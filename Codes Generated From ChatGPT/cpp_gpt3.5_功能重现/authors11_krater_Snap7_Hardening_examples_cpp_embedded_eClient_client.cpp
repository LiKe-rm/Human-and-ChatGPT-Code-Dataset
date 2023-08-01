#include <iostream>
#include <iomanip>
#include <chrono>
#include "snap7/s7client.h"

using namespace std;

void CliCompletion(void* usrPtr, int opCode, int opResult) {
	cout << "Operation completed with result: " << opResult << endl;
}

void Usage() {
	cout << "Usage: snap7_example ip_address" << endl;
}

void hexdump(const void* data, size_t size) {
	const uint8_t* p = reinterpret_cast<const uint8_t*>(data);
	size_t i = 0;
	while (i < size) {
		cout << hex << setw(2) << setfill('0') << static_cast<unsigned int>(p[i]) << " ";
		i++;
		if (i % 16 == 0) {
			cout << " ";
			for (size_t j = i - 16; j < i; j++) {
				if (p[j] >= 32 && p[j] <= 126) {
					cout << static_cast<char>(p[j]);
				}
				else {
					cout << ".";
				}
			}
			cout << endl;
		}
	}
	if (i % 16 != 0) {
		size_t spaces = (16 - i % 16) * 3 + 1;
		for (size_t j = 0; j < spaces; j++) {
			cout << " ";
		}
		for (size_t j = i - (i % 16); j < size; j++) {
			if (p[j] >= 32 && p[j] <= 126) {
				cout << static_cast<char>(p[j]);
			}
			else {
				cout << ".";
			}
		}
		cout << endl;
	}
}

void Check(int result, const char* function, const char* operation) {
	if (result != 0) {
		cout << function << " failed with error code " << result << endl;
	}
	else {
		cout << operation << " successful" << endl;
	}
}

void MultiRead(S7Client* client) {
	cout << "Reading multiple S7 variables" << endl;

	uint16_t db_nr = 1;
	uint16_t vars[] = { 0, 10, 20 };
	uint16_t amount = sizeof(vars) / sizeof(vars[0]);

	uint16_t result[amount];
	int res = client->MBRead(db_nr, vars, amount, S7WLWord, result);

	Check(res, "MBRead", "Reading multiple S7 variables");

	cout << "Values:" << endl;
	for (int i = 0; i < amount; i++) {
		cout << "DB" << db_nr << ".W" << vars[i] << ": " << result[i] << endl;
	}
}

void ListBlocks(S7Client* client) {
	cout << "Listing blocks" << endl;

	S7BlockInfo* block_list = nullptr;
	int num_blocks = client->ListBlocks(&block_list);

	if (num_blocks <= 0) {
		cout << "No blocks found" << endl;
		return;
	}

	cout << "Found " << num_blocks << " blocks:" << endl;

	for (int i = 0; i < num_blocks; i++) {
		cout << "Block " << i << ":" << endl;
		cout << "Block type: " << block_list[i].BlkType << endl;
		cout << "Block number:
			" << block_list[i].BlkNumber << endl;
			cout << "Block language: " << block_list[i].BlkLang << endl;
		cout << "Block flags: " << block_list[i].BlkFlags << endl;
		cout << "Block name: " << block_list[i].BlkName << endl;
	}
	client->Free(block_list);
}

void OrderCode(S7Client* client) {
	cout << "Getting CPU order code" << endl;
	uint8_t order_code[20];
	int res = client->GetOrderCode(order_code);

	Check(res, "GetOrderCode", "Getting CPU order code");

	cout << "CPU order code: " << order_code << endl;
}

void CpuInfo(S7Client* client) {
	cout << "Getting CPU info" << endl;
	S7CpuInfo cpu_info;
	int res = client->GetCpuInfo(&cpu_info);

	Check(res, "GetCpuInfo", "Getting CPU info");

	cout << "Module type: " << cpu_info.ModuleTypeName << endl;
	cout << "Serial number: " << cpu_info.SerialNumber << endl;
	cout << "AS name: " << cpu_info.ASName << endl;
	cout << "ModuleName: " << cpu_info.ModuleName << endl;
	cout << "Plant ID: " << cpu_info.PlantID << endl;
	cout << "Module location: " << cpu_info.ModuleLocation << endl;
	cout << "Vendor ID: " << cpu_info.VendorID << endl;
}

void CpInfo(S7Client* client) {
	cout << "Getting communication processor info" << endl;
	S7CpInfo cp_info;
	int res = client->GetCpInfo(&cp_info);

	Check(res, "GetCpInfo", "Getting communication processor info");

	cout << "Max PDU length: " << cp_info.MaxPduLength << endl;
	cout << "Max connections: " << cp_info.MaxConnections << endl;
	cout << "Max MPI rate: " << cp_info.MaxMpiRate << endl;
	cout << "Max telegram length: " << cp_info.MaxTelegramLength << endl;
	cout << "Max bus users: " << cp_info.MaxBusUsers << endl;
}

void UnitStatus(S7Client* client) {
	cout << "Getting PLC status" << endl;
	uint16_t status;
	int res = client->GetPlcStatus(&status);

	Check(res, "GetPlcStatus", "Getting PLC status");

	cout << "PLC status: " << hex << status << endl;
}

void UploadDB0(S7Client* client) {
	cout << "Uploading DB0 block" << endl;
	uint8_t* data = nullptr;
	int size = client->DBRead(0, 0, 100, data);

	Check(size, "DBRead", "Reading DB0 block");

	cout << "DB0 block content:" << endl;
	hexdump(data, size);

	client->Free(data);
}

void AsCBUploadDB0(S7Client* client) {
	cout << "Uploading DB0 block asynchronously (using callback)" << endl;
	auto start_time = chrono::high_resolution_clock::now();

	int res = client->AsReadArea(S7AreaDB, 0, 0, 100, S7WLByte, CliCompletion, nullptr);

	Check(res, "AsReadArea", "Starting asynchronous read");

	auto end_time = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
	cout << "Started asynchronous read (using callback) in " << duration << " microseconds" << endl;
}

void AsEWUploadDB0(S7Client* client) {
	cout << "Uploading DB0 block asynchronously (using event wait)" << endl;
	auto start_time = chrono::high_resolution_clock::now();

	int res = client->AsReadArea(S7AreaDB, 0, 0, 100, S7WLByte, nullptr, nullptr);

	Check(res, "AsReadArea", "Starting asynchronous read");

	bool done = false;
	while (!done) {
		int status = client->WaitAsCompletion(1000);

		if (status == 0) {
			done = true;
		}
		else if (status == -1) {
			cout << "WaitAsCompletion failed" << endl;
			return;
		}
	}

	auto end_time = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

	cout << "Started asynchronous read (using event wait) in " << duration << " microseconds" << endl;
}

void ReadSzl_0011_0000(S7Client* client) {
	cout << "Reading SZL block 0x0011/0x0000" << endl;
	uint16_t id = 0x0011;
	uint16_t index = 0x0000;

	uint8_t* data = nullptr;
	int size = client->ReadSZL(id, index, data);

	Check(size, "ReadSZL", "Reading SZL block");

	cout << "SZL block content:" << endl;
	hexdump(data, size);

	client->Free(data);
}

void Up_DownloadFC1(S7Client* client) {
	cout << "Uploading and downloading FC1 block" << endl;
	uint8_t* data = nullptr;
	int size = client->DBRead(1, 0, 100, data);

	Check(size, "DBRead", "Reading FC1 block");

	int res = client->DBWrite(2, 0, size, data);

	Check(res, "DBWrite", "Writing FC1 block");

	client->Free(data);
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		Usage();
		return 0;
	}
	S7Client client;
	int res = client.ConnectTo(argv[1], 0, 1);

	if (res != 0) {
		cout << "Connection failed" << endl;
		return 1;
	}
	MultiRead(&client);
	ListBlocks(&client);
	OrderCode(&client);
	CpuInfo(&client);
	CpInfo(&client);
	UnitStatus(&client);
	UploadDB0(&client);
	AsCBUploadDB0(&client);
	AsEWUploadDB0(&client);
	AsPOUploadDB0(&client);
	ReadSzl_0011_0000(&client);
	Up_DownloadFC1(&client);

	client.Disconnect();

	return 0;
}

