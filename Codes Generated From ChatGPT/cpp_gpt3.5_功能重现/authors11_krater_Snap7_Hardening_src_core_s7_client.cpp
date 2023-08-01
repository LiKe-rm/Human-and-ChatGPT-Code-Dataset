#include <iostream>
#include <cstring>
#include <cstdlib>
#include "snap7/snap7-client.h"

using namespace std;

class TSnap7Client {
public:
	TSnap7Client();
	~TSnap7Client();
	int Connect(const char* address, int rack, int slot);
	void Disconnect();
	int ReadArea(int areaCode, int dbNum, int start, int amount, void* buffer);
	int WriteArea(int areaCode, int dbNum, int start, int amount, void* buffer);
	void StartAsyncJob();
	int WaitAsCompletion(int* opCode, int* result);
private:
	S7Object client;
	int asyncJobId;
};

TSnap7Client::TSnap7Client() {
	client = Cli_Create();
	asyncJobId = 0;
}

TSnap7Client::~TSnap7Client() {
	Cli_Destroy(&client);
}

int TSnap7Client::Connect(const char* address, int rack, int slot) {
	int result = Cli_ConnectTo(client, address, rack, slot);
	if (result == 0) {
		cout << "Connected to PLC " << address << " Rack " << rack << " Slot " << slot << endl;
	}
	else {
		cout << "Failed to connect to PLC " << address << " Rack " << rack << " Slot " << slot << endl;
	}
	return result;
}

void TSnap7Client::Disconnect() {
	Cli_Disconnect(client);
	cout << "Disconnected from PLC" << endl;
}

int TSnap7Client::ReadArea(int areaCode, int dbNum, int start, int amount, void* buffer) {
	return Cli_ReadArea(client, areaCode, dbNum, start, amount, buffer);
}

int TSnap7Client::WriteArea(int areaCode, int dbNum, int start, int amount, void* buffer) {
	return Cli_WriteArea(client, areaCode, dbNum, start, amount, buffer);
}

void TSnap7Client::StartAsyncJob() {
	asyncJobId = Cli_AsyncReadArea(client, S7AreaDB, 1, 0, 10);
}

int TSnap7Client::WaitAsCompletion(int* opCode, int* result) {
	return Cli_AsyncComplete(client, &asyncJobId, opCode, result);
}

int main() {
	TSnap7Client client;
	const char* address = "192.168.1.10";
	int rack = 0;
	int slot = 2;
	int dbNum = 1;
	int start = 0;
	int amount = 10;
	uint8_t buffer[amount];

	if (client.Connect(address, rack, slot) == 0) {
		if (client.ReadArea(S7AreaDB, dbNum, start, amount, buffer) == 0) {
			cout << "Read data from DB " << dbNum << ", start from " << start << ", amount " << amount << endl;
			for (int i = 0; i < amount; i++) {
				cout << "Byte " << i << " = " << (int)buffer[i] << endl;
			}
		}
		else {
			cout << "Failed to read data from DB " << dbNum << ", start from " << start << ", amount " << amount << endl;
		}

		buffer[0] = 0x01;
		buffer[1] = 0x02;
		buffer[2] = 0x03;

		if (client.WriteArea(S7AreaDB, dbNum, start, amount, buffer) == 0) {
			cout << "Write data to DB " << dbNum << ", start from " << start << ", amount " << amount << endl;
		}
		else {
			cout << "Failed to write data to DB " << dbNum << ", start from " << start << ", amount " << amount << endl;
		}
		client.StartAsyncJob();
		int opCode = 0;
		int result = 0;

		if (client.WaitAsCompletion(&opCode, &result) == 0) {
			if (opCode == S7_OP_READ && result == 0) {
				cout << "Async read operation completed successfully" << endl;
			}
			else {
				cout << "Async operation completed with error: OpCode " << opCode << ", Result " << result << endl;
			}
		}
		else {
			cout << "Failed to complete async operation" << endl;
		}

		client.Disconnect();
	}
	else {
		cout << "Failed to connect to PLC" << endl;
	}

	return 0;
}
