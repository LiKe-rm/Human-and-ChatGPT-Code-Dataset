#include <iostream>
#include <string>
#include <ctime>
#include <map>
#include <vector>
#include <cstdlib>
#include <chrono>

class KeyAuth
{
public:
	bool login(const std::string& username, const std::string& password)
	{
		auto user = users.find(username);
		if (user != users.end())
		{
			return user->second.password == password;
		}
		return false;
	}

	bool registerUser(const std::string& username, const std::string& password, const std::string& licenseKey)
	{
		if (users.find(username) != users.end())
		{
			return false;
		}

		if (licenseKeys.find(licenseKey) == licenseKeys.end())
		{
			return false;
		}

		User newUser{ username, password, licenseKey, generateHardwareID(), getCurrentTimestamp(), getCurrentTimestamp() };
		users[username] = newUser;
		return true;
	}

	bool upgrade(const std::string& username, const std::string& licenseKey)
	{
		auto user = users.find(username);
		if (user == users.end())
		{
			return false;
		}

		if (licenseKeys.find(licenseKey) == licenseKeys.end())
		{
			return false;
		}

		user->second.licenseKey = licenseKey;
		return true;
	}

	bool verifyLicenseKey(const std::string& licenseKey)
	{
		return licenseKeys.find(licenseKey) != licenseKeys.end();
	}

	void displayAppData()
	{
		std::cout << "在线用户数: " << onlineUsers << std::endl;
		std::cout << "注册用户数: " << users.size() << std::endl;
		std::cout << "许可密钥数量: " << licenseKeys.size() << std::endl;
		std::cout << "应用程序版本: " << appVersion << std::endl;
	}

	void displayUserData(const std::string& username)
	{
		auto user = users.find(username);
		if (user != users.end())
		{
			std::cout << "用户名: " << user->second.username << std::endl;
			std::cout << "IP地址: " << user->second.ipAddress << std::endl;
			std::cout << "硬件ID: " << user->second.hardwareID << std::endl;
			std::cout << "创建日期: " << user->second.creationDate << std::endl;
			std::cout << "最后登录日期: " << user->second.lastLoginDate << std::endl;
		}
		else
		{
			std::cout << "用户不存在." << std::endl;
		}
	}

private:
	struct User
	{
		std::string username;
		std::string password;
		std::string licenseKey;
		std::string hardwareID;
		std::time_t creationDate;
		std::time_t lastLoginDate;
	};

	std::map<std::string, User> users;
	std::map<std::string, int> licenseKeys = { {"KEY-123", 0}, {"KEY-456", 0}, {"KEY-789", 0} };
	int onlineUsers = 0;
	const std::string appVersion = "1.0.0";

	std::string generateHardwareID()
	{
		std::string hardwareID = "HWID-";
		for (int i = 0; i < 6; i++)
		{
			hardwareID += 'A' + rand() % 26;
		}
		return hardwareID;
	}

	std::time_t getCurrentTimestamp()
	{
		auto now = std::chrono::system_clock::now();
		return std::chrono::system_clock::to_time_t(now);
	}
};

int main()
{
	KeyAuth keyAuth;
	std::string username, password, licenseKey;
	int choice;
	keyAuth.displayAppData();
	std::cout << "请选择操作:\n"
		"1. 登录\n"
		"2. 注册\n"
		"3. 升级\n"
		"4. 仅使用许可密钥验证\n"
		"5. 退出\n";
	std::cin >> choice;

	while (choice != 5)
	{
		switch (choice)
		{
		case 1:
			std::cout << "输入用户名: ";
			std::cin >> username;
			std::cout << "输入密码: ";
			std::cin >> password;

			if (keyAuth.login(username, password))
			{
				std::cout << "登录成功!\n";
				keyAuth.displayUserData(username);
			}
			else
			{
				std::cout << "登录失败.\n";
			}
			break;
		case 2:
			std::cout << "输入用户名: ";
			std::cin >> username;
			std::cout << "输入密码: ";
			std::cin >> password;
			std::cout << "输入许可密钥: ";
			std::cin >> licenseKey;

			if (keyAuth.registerUser(username, password, licenseKey))
			{
				std::cout << "注册成功!\n";
			}
			else
			{
				std::cout << "注册失败.\n";
			}
			break;
		case 3:
			std::cout << "输入用户名: ";
			std::cin >> username;
			std::cout << "输入许可密钥: ";
			std::cin >> licenseKey;

			if (keyAuth.upgrade(username, licenseKey))
			{
				std::cout << "升级成功!\n";
			}
			else
			{
				std::cout << "升级失败.\n";
			}
			break;
		case 4:
			std::cout << "输入许可密钥: ";
			std::cin >> licenseKey;

			if (keyAuth.verifyLicenseKey(licenseKey))
			{
				std::cout << "密钥验证成功!\n";
			}
			else
			{
				std::cout << "密钥验证失败.\n";
			}
			break;
		default:
			std::cout << "无效的选择.\n";
		}

		std::cout << "请选择操作:\n"
			"1. 登录\n"
			"2. 注册\n"
			"3. 升级\n"
			"4. 仅使用许可密钥验证\n"
			"5. 退出\n";
		std::cin >> choice;
	}

	return 0;
}