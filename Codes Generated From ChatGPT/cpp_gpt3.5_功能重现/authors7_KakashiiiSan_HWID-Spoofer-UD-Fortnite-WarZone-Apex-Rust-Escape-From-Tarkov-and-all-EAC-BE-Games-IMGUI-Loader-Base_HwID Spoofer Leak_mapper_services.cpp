#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h>

class DriverLoader {
public:
	bool load_driver(const std::wstring& driver_path);
	bool unload_driver();
	bool clean_up();

private:
	std::wstring create_file_path(const std::wstring& driver_data);
	bool delete_file(const std::wstring& file_path);
	bool create_service_reg_key(const std::wstring& driver_path);
	bool delete_service_reg_key();
	bool escalate_privilege();

	std::wstring service_name = L"DriverLoaderService";
	std::wstring temp_file_path;
	HKEY hServiceKey = nullptr;
};

bool DriverLoader::load_driver(const std::wstring& driver_path) {
	temp_file_path = create_file_path(driver_path);
	if (temp_file_path.empty()) {
		return false;
	}

	if (!escalate_privilege()) {
		return false;
	}

	if (!create_service_reg_key(temp_file_path)) {
		return false;
	}

	std::wstring encrypted_driver_path = L"\\??\\" + temp_file_path;
	UNICODE_STRING driver_path_unicode;
	RtlInitUnicodeString(&driver_path_unicode, encrypted_driver_path.c_str());
	NTSTATUS status = NtLoadDriver(&driver_path_unicode);

	return NT_SUCCESS(status);
}

bool DriverLoader::unload_driver() {
	std::wstring encrypted_driver_path = L"\\??\\" + temp_file_path;
	UNICODE_STRING driver_path_unicode;
	RtlInitUnicodeString(&driver_path_unicode, encrypted_driver_path.c_str());
	NTSTATUS status = NtUnloadDriver(&driver_path_unicode);

	return NT_SUCCESS(status);
}

bool DriverLoader::clean_up() {
	if (!delete_file(temp_file_path)) {
		return false;
	}

	if (!delete_service_reg_key()) {
		return false;
	}

	return true;
}

std::wstring DriverLoader::create_file_path(const std::wstring& driver_data) {
	TCHAR temp_path[MAX_PATH];
	if (GetTempPath(MAX_PATH, temp_path) == 0) {
		return L"";
	}

	TCHAR temp_file[MAX_PATH];
	if (GetTempFileName(temp_path, service_name.c_str(), 0, temp_file) == 0) {
		return L"";
	}

	HANDLE hFile = CreateFile(temp_file, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (hFile == INVALID_HANDLE_VALUE) {
		return L"";
	}

	DWORD bytes_written;
	if (!WriteFile(hFile, driver_data.c_str(), driver_data.size() * sizeof(wchar_t), &bytes_written, nullptr)) {
		CloseHandle(hFile);
		return L"";
	}

	CloseHandle(hFile);
	return temp_file;
}

bool DriverLoader::delete_file(const std::wstring& file_path) {
	return DeleteFile(file_path.c_str()) != 0;
}

bool DriverLoader::create_service_reg_key(const std::wstring& driver_path) {
	HKEY hKey;
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, (L"System\\CurrentControlSet\\Services\\" + service_name).c_str(), 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE, nullptr, &hKey, nullptr) != ERROR_SUCCESS) {
		return false;
	}

	if (RegSetValueEx(hKey, L"ImagePath", 0, REG_SZ, reinterpret_cast<const BYTE*>(driver_path.c_str()), (driver_path.size() + 1) * sizeof(wchar_t)) != ERROR_SUCCESS) {

		RegCloseKey(hKey);
		return false;
	}

	DWORD type = 1; // SERVICE_KERNEL_DRIVER
	if (RegSetValueEx(hKey, L"Type", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&type), sizeof(type)) != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		return false;
	}

	DWORD start = 3; // SERVICE_DEMAND_START
	if (RegSetValueEx(hKey, L"Start", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&start), sizeof(start)) != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		return false;
	}

	RegCloseKey(hKey);
	hServiceKey = hKey;
	return true;
}

bool DriverLoader::delete_service_reg_key() {
	if (hServiceKey) {
		RegCloseKey(hServiceKey);
	}
	if (RegDeleteKey(HKEY_LOCAL_MACHINE, (L"System\\CurrentControlSet\\Services\\" + service_name).c_str()) != ERROR_SUCCESS) {
		return false;
	}

	return true;
}

bool DriverLoader::escalate_privilege() {
	HANDLE hToken;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		return false;
	}
	LUID luid;
	if (!LookupPrivilegeValue(nullptr, SE_LOAD_DRIVER_NAME, &luid)) {
		CloseHandle(hToken);
		return false;
	}

	TOKEN_PRIVILEGES tp;
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr)) {
		CloseHandle(hToken);
		return false;
	}

	CloseHandle(hToken);
	return true;
}

int main() {
	std::wstring driver_path = L"C:\path\to\your\driver.sys";
	DriverLoader loader;
	if (!loader.load_driver(driver_path)) {
		std::cerr << "Failed to load driver" << std::endl;
		return 1;
	}

	// Do some work with the driver

	if (!loader.unload_driver()) {
		std::cerr << "Failed to unload driver" << std::endl;
		return 1;
	}

	if (!loader.clean_up()) {
		std::cerr << "Failed to clean up" << std::endl;
		return 1;
	}

	return 0;
}