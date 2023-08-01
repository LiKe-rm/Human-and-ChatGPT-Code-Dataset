#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <winreg.h>

class DriverLoader {
public:
	DriverLoader(const std::wstring& service_name);
	~DriverLoader();
	bool load_driver(const std::wstring& driver_binary);
	bool unload_driver();

private:
	std::wstring service_name_;
	std::wstring driver_file_path_;

	std::wstring create_file_path(const std::wstring& driver_binary);
	void delete_file();
	bool create_service_reg_key();
	bool delete_service_reg_key();
	bool escalate_privilege();
};

DriverLoader::DriverLoader(const std::wstring& service_name) : service_name_(service_name) {}

DriverLoader::~DriverLoader() {
	clean_up();
}

std::wstring DriverLoader::create_file_path(const std::wstring& driver_binary) {
	wchar_t temp_path[MAX_PATH];
	GetTempPath(MAX_PATH, temp_path);
	std::wstring file_path(temp_path);
	file_path += L"\\";
	file_path += service_name_;
	file_path += L".sys";

	std::ifstream src(driver_binary, std::ios::binary);
	std::ofstream dest(file_path, std::ios::binary);
	dest << src.rdbuf();

	return file_path;
}

void DriverLoader::delete_file() {
	DeleteFile(driver_file_path_.c_str());
}

bool DriverLoader::create_service_reg_key() {
	HKEY hKey;
	std::wstring subkey = L"System\\CurrentControlSet\\Services\\" + service_name_;

	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, subkey.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS, NULL, &hKey, NULL) != ERROR_SUCCESS) {
		return false;
	}

	DWORD value = 1;
	if (RegSetValueEx(hKey, L"Type", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), sizeof(value)) != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		return false;
	}

	value = 3;
	if (RegSetValueEx(hKey, L"Start", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), sizeof(value)) != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		return false;
	}

	value = 1;
	if (RegSetValueEx(hKey, L"ErrorControl", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), sizeof(value)) != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		return false;
	}

	if (RegSetValueEx(hKey, L"ImagePath", 0, REG_EXPAND_SZ, reinterpret_cast<const BYTE*>(driver_file_path_.c_str()),
		(driver_file_path_.size() + 1) * sizeof(wchar_t)) != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		return false;
	}

	RegCloseKey(hKey);
	return true;
}

bool DriverLoader::delete_service_reg_key() {
	std::wstring subkey = L"System\\CurrentControlSet\\Services\\" + service_name_;
	return RegDeleteKey(HKEY_LOCAL_MACHINE, subkey.c_str()) == ERROR_SUCCESS;
}

bool DriverLoader::escalate_privilege() {
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		return false;
	}

	LookupPrivilegeValue(NULL, SE_LOAD_DRIVER_NAME, &tkp.Privileges[0].Luid);

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	bool result = AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL);
	CloseHandle(hToken);
	return result;
}

bool DriverLoader::load_driver(const std::wstring& driver_binary) {
	driver_file_path_ = create_file_path(driver_binary);
	if (!create_service_reg_key()) {
		return false;
	}
	if (!escalate_privilege()) {
		return false;
	}

	std::wstring registry_path = L"\\Registry\\Machine\\System\\CurrentControlSet\\Services\\" + service_name_;
	UNICODE_STRING driver_service;
	RtlInitUnicodeString(&driver_service, registry_path.c_str());

	NTSTATUS status = NtLoadDriver(&driver_service);
	if (!NT_SUCCESS(status)) {
		clean_up();
		return false;
	}

	return true;
}

bool DriverLoader::unload_driver() {
	std::wstring registry_path = L"\Registry\Machine\System\CurrentControlSet\Services\" + service_name_;
		UNICODE_STRING driver_service;
	RtlInitUnicodeString(&driver_service, registry_path.c_str());
	NTSTATUS status = NtUnloadDriver(&driver_service);
	if (!NT_SUCCESS(status)) {
		return false;
	}

	clean_up();
	return true;
}

void DriverLoader::clean_up() {
	delete_service_reg_key();
	delete_file();
}

int main() {
	std::wstring service_name = L"TestDriver";
	std::wstring driver_binary = L"C:\path\to\driver.sys";
	DriverLoader loader(service_name);

	if (loader.load_driver(driver_binary)) {
		std::cout << "Driver loaded successfully." << std::endl;
		// Perform actions that require the driver...

		if (loader.unload_driver()) {
			std::cout << "Driver unloaded successfully." << std::endl;
		}
		else {
			std::cerr << "Failed to unload driver." << std::endl;
		}
	}
	else {
		std::cerr << "Failed to load driver." << std::endl;
	}

	return 0;
}