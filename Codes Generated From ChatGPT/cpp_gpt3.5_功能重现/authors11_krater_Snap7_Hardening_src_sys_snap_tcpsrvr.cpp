#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "snap7/snap7.h"

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

// 服务器事件枚举
enum class ServerEvent {
	Started,
	Stopped,
	ClientConnected,
	ClientDisconnected,
	DataReceived,
	Error
};

class TcpServer {
public:
	// 服务器事件回调函数类型
	typedef std::function<void(ServerEvent event, void* data)> ServerEventCallback;

	TcpServer(int port, ServerEventCallback event_callback) :
		port_(port),
		event_callback_(event_callback),
		stop_(false)
	{
		// 初始化Snap7库
		if (Snap7::Init() != 0) {
			event_callback_(ServerEvent::Error, (void*)"Failed to initialize Snap7 library");
			return;
		}

		// 创建监听线程
		listener_thread_ = std::thread(&TcpServer::ListenerThread, this);

		// 创建工作线程
		worker_thread_ = std::thread(&TcpServer::WorkerThread, this);

		event_callback_(ServerEvent::Started, nullptr);
	}

	~TcpServer() {
		// 停止监听线程
		stop_ = true;
		listener_thread_.join();

		// 停止工作线程
		worker_thread_.join();

		// 关闭Snap7库
		Snap7::Cleanup();
	}

private:
	int port_;
	ServerEventCallback event_callback_;
	bool stop_;

	// 事件队列
	std::queue<std::pair<ServerEvent, void*>> event_queue_;
	std::mutex event_queue_mutex_;
	std::condition_variable event_queue_cv_;

	// 客户端连接信息
	struct ClientInfo {
		int fd;
		uint8_t buffer[BUFFER_SIZE];
		int buffer_size;
		S7Object s7_client;
	};

	// 客户端列表
	std::vector<ClientInfo> clients_;
	std::mutex clients_mutex_;

	// 线程对象
	std::thread listener_thread_;
	std::thread worker_thread_;

	void ListenerThread() {
		// 创建服务器socket
		int server_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (server_fd == -1) {
			event_callback_(ServerEvent::Error, (void*)"Failed to create server socket");
			return;
		}

		// 设置socket选项
		int option = 1;
		if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option))) {
			event_callback_(ServerEvent::Error, (void*)"Failed to set server socket options");
			return;
		}

		// 绑定服务器地址
		struct sockaddr_in address;
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons(port_);

		if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
			event_callback_(ServerEvent::Error, (void*)"Failed to bind server socket");
			return;
		}

		// 开始监听
		if (listen(server_fd, MAX_CLIENTS) < 0) {
			event_callback_(ServerEvent::Error, (void*)"Failed to start server listener");
			return;
		}

		while (!stop_) {
			// 等待客户端连接
			struct sockaddr_in client_address;
			socklen_t        client_address_length = sizeof(client_address);
			int client_fd = accept(server_fd, (struct sockaddr*)&client_address, &client_address_length);
			if (client_fd < 0) {
				event_callback_(ServerEvent::Error, (void*)"Failed to accept client connection");
				continue;
			}

			// 添加客户端到列表
			clients_mutex_.lock();
			if (clients_.size() >= MAX_CLIENTS) {
				event_callback_(ServerEvent::Error, (void*)"Max number of clients reached");
				close(client_fd);
			}
			else {
				ClientInfo client_info;
				client_info.fd = client_fd;
				client_info.buffer_size = 0;
				client_info.s7_client = Snap7::Create();
				clients_.push_back(client_info);
				event_callback_(ServerEvent::ClientConnected, (void*)&client_fd);
			}
			clients_mutex_.unlock();
		}

		// 关闭服务器socket
		close(server_fd);
	}

	void WorkerThread() {
		while (!stop_) {
			// 从事件队列中获取事件
			std::pair<ServerEvent, void*> event;
			{
				std::unique_lock<std::mutex> lock(event_queue_mutex_);
				event_queue_cv_.wait(lock, [this]() { return !event_queue_.empty() || stop_; });
				if (stop_) break;
				event = event_queue_.front();
				event_queue_.pop();
			}

			// 处理事件
			switch (event.first) {
			case ServerEvent::ClientDisconnected:
				HandleClientDisconnected(*static_cast<int*>(event.second));
				break;
			case ServerEvent::DataReceived:
				HandleDataReceived(*static_cast<int*>(event.second));
				break;
			default:
				break;
			}
		}

		// 断开所有客户端连接
		clients_mutex_.lock();
		for (auto& client : clients_) {
			close(client.fd);
			Snap7::Destroy(client.s7_client);
		}
		clients_.clear();
		clients_mutex_.unlock();
	}

	void HandleClientDisconnected(int client_fd) {
		// 从客户端列表中移除客户端
		clients_mutex_.lock();
		auto it = std::find_if(clients_.begin(), clients_.end(), [client_fd](const ClientInfo& client) { return client.fd == client_fd; });
		if (it != clients_.end()) {
			event_callback_(ServerEvent::ClientDisconnected, (void*)&client_fd);
			Snap7::Destroy(it->s7_client);
			clients_.erase(it);
		}
		clients_mutex_.unlock();

		// 关闭socket
		close(client_fd);
	}

	void HandleDataReceived(int client_fd) {
		// 从客户端列表中查找客户端
		clients_mutex_.lock();
		auto it = std::find_if(clients_.begin(), clients_.end(), [client_fd](const ClientInfo& client) { return client.fd == client_fd; });
		if (it == clients_.end()) {
			clients_mutex_.unlock();
			return;
		}
		ClientInfo& client = *it;
		clients_mutex_.unlock();

		// 处理数据
		int read_size = read(client_fd, client.buffer + client.buffer_size, BUFFER_SIZE - client.buffer_size);
		if (read_size == -1) {
			event_callback_(ServerEvent::Error, (void*)"Failed to read client data");
			HandleClientDisconnected(client_fd);
			return;
		}
		else if (read_size == 0) {
			HandleClientDisconnected(client_fd);
			return;
		}
		client.buffer_size += read_size;

		// 尝试解
		while (client.buffer_size >= 12) {
			// 解析Snap7数据包头
			uint16_t pdu_size;
			memcpy(&pdu_size, client.buffer + 2, sizeof(uint16_t));
			pdu_size = ntohs(pdu_size);

			// 检查数据包是否完整
			if (client.buffer_size < pdu_size + 6) {
				break;
			}

			// 处理数据包
			S7Object s7_object = client.s7_client;
			S7CpObject cp_object = Snap7::CreateS7CpObject();
			Snap7::SetAsClient(cp_object, 2, 2);
			int result = Snap7::CliS7Dispatch(s7_object, cp_object, client.buffer + 4, pdu_size + 2, nullptr, nullptr);
			Snap7::DestroyS7CpObject(cp_object);
			if (result == -1) {
				event_callback_(ServerEvent::Error, (void*)"Failed to process client data");
				HandleClientDisconnected(client_fd);
				return;
			}

			// 移除处理完成的数据包
			std::memmove(client.buffer, client.buffer + pdu_size + 6, client.buffer_size - pdu_size - 6);
			client.buffer_size -= pdu_size + 6;

			event_callback_(ServerEvent::DataReceived, (void*)&client_fd);
		}
	}
public:
	// 发送数据给客户端
	void SendData(int client_fd, const void* data, size_t size) {
		send(client_fd, data, size, 0);
	}
	// 停止服务器
	void Stop() {
		stop_ = true;
	}

	// 获取事件队列中的下一个事件
	std::pair<ServerEvent, void*> GetNextEvent() {
		std::unique_lock<std::mutex> lock(event_queue_mutex_);
		event_queue_cv_.wait(lock, [this]() { return !event_queue_.empty() || stop_; });
		if (stop_) return { ServerEvent::Error, (void*)"Server stopped" };
		auto event = event_queue_.front();
		event_queue_.pop();
		return event;
	}
private:
	// 将事件添加到事件队列
	void AddEvent(ServerEvent event, void* data) {
		std::lock_guardstd::mutex lock(event_queue_mutex_);
		event_queue_.push({ event, data });
		event_queue_cv_.notify_one();
	}
};

int main() {
	// 创建服务器对象
	TcpServer server(1024, [](ServerEvent event, void* data) {
		switch (event) {
		case ServerEvent::Started:
			std::cout << "Server started" << std::endl;
			break;
		case ServerEvent::Stopped:
			std::cout << "Server stopped" << std::endl;
			break;
		case ServerEvent::ClientConnected:
			std::cout << "Client connected" << std::endl;
			break;
		case ServerEvent::ClientDisconnected:
			std::cout << "Client disconnected" << std::endl;
			break;
		case ServerEvent::DataReceived:
			std::cout << "Data received" << std::endl;
			break;
		case ServerEvent::Error:
			std::cout << "Error: " << (const char*)data << std::endl;
			break;
		default:
			break;
		}
		});
	// 处理客户端连接和通讯
	while (true) {
		auto event = server.GetNextEvent();
		if (event.first == ServerEvent::Error) {
			std        cout << "Error: " << (const char*)event.second << endl;
			break;
		}

		switch (event.first) {
		case ServerEvent::ClientConnected: {
			int client_fd = *(int*)event.second;
			server.SendData(client_fd, "Welcome to the server!", strlen("Welcome to the server!"));
			break;
		}
		case ServerEvent::DataReceived: {
			int client_fd = *(int*)event.second;
			server.SendData(client_fd, "Received your data!", strlen("Received your data!"));
			break;
		}
		default:
			break;
		}
	}

	// 停止服务器
	server.Stop();

	// 等待服务器停止
	while (true) {
		auto event = server.GetNextEvent();
		if (event.first == ServerEvent::Error) {
			cout << "Error: " << (const char*)event.second << endl;
			break;
		}
		else if (event.first == ServerEvent::Stopped) {
			cout << "Server stopped" << endl;
			break;
		}
	}

	return 0;
}

