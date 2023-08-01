#include <iostream>
#include <string>
#include <Windows.h>
#include <TlHelp32.h>

class kernelmode_proc_handler {
public:
	kernelmode_proc_handler() {
		hDriver = CreateFileW(L"\\\\.\\YourKernelDriver", GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
	}

	~kernelmode_proc_handler() {
		CloseHandle(hDriver);
	}

	bool process_exists(const std::wstring& process_name, DWORD& pid) {
		PROCESSENTRY32W entry;
		entry.dwSize = sizeof(PROCESSENTRY32W);

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (snapshot == INVALID_HANDLE_VALUE) return false;

		if (Process32FirstW(snapshot, &entry)) {
			do {
				if (std::wstring(entry.szExeFile) == process_name) {
					pid = entry.th32ProcessID;
					CloseHandle(snapshot);
					return true;
				}
			} while (Process32NextW(snapshot, &entry));
		}

		CloseHandle(snapshot);
		return false;
	}

	bool attach_to_process(const std::wstring& process_name) {
		DWORD pid;
		if (!process_exists(process_name, pid)) return false;

		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		if (!hProcess) return false;

		CloseHandle(hProcess);
		return true;
	}

	uintptr_t get_module_base_address(DWORD pid, const std::wstring& module_name) {
		uintptr_t module_base_address = 0;
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
		if (hSnapshot != INVALID_HANDLE_VALUE) {
			MODULEENTRY32W module_entry;
			module_entry.dwSize = sizeof(MODULEENTRY32W);
			if (Module32FirstW(hSnapshot, &module_entry)) {
				do {
					if (module_entry.szModule == module_name) {
						module_base_address = (uintptr_t)module_entry.modBaseAddr;
						break;
					}
				} while (Module32NextW(hSnapshot, &module_entry));
			}
		}
		CloseHandle(hSnapshot);
		return module_base_address;
	}

	bool read_memory(uintptr_t src, PVOID dest, SIZE_T size) {
		DWORD bytesRead;
		return DeviceIoControl(hDriver, YOUR_READ_MEMORY_IOCTL_CODE, &src, sizeof(src), dest, size, &bytesRead, nullptr);
	}

	bool write_memory(PVOID src, uintptr_t dest, SIZE_T size) {
		DWORD bytesWritten;
		return DeviceIoControl(hDriver, YOUR_WRITE_MEMORY_IOCTL_CODE, src, size, &dest, sizeof(dest), &bytesWritten, nullptr);
	}

	bool change_memory_protection(uintptr_t address, SIZE_T size, DWORD new_protect) {
		DWORD oldProtect;
		return DeviceIoControl(hDriver, YOUR_CHANGE_MEMORY_PROTECTION_IOCTL_CODE, &address, sizeof(address), &new_protect, sizeof(new_protect), &oldProtect, nullptr);
	}

	LPVOID allocate_memory(SIZE_T size) {
		LPVOID address = nullptr;
		SIZE_T bytesReturned;
		return Device
			IoControl(hDriver, YOUR_ALLOCATE_MEMORY_IOCTL_CODE, &size, sizeof(size), &address, sizeof(address), &bytesReturned, nullptr) ? address : nullptr;
	}

private:
	HANDLE hDriver;
};

int main() {
	// 注意: 在运行此程序之前，确保内核驱动程序已加载并启动
	// 请以管理员身份运行此程序
	kernelmode_proc_handler handler;
	std::wstring process_name = L"your_target_process.exe";
	if (!handler.attach_to_process(process_name)) {
		std::wcout << L"Failed to attach to process: " << process_name << std::endl;
		return 1;
	}

	DWORD pid;
	if (!handler.process_exists(process_name, pid)) {
		std::wcout << L"Process not found: " << process_name << std::endl;
		return 1;
	}

	std::wstring module_name = L"your_target_module.dll";
	uintptr_t module_base_address = handler.get_module_base_address(pid, module_name);
	if (!module_base_address) {
		std::wcout << L"Module not found: " << module_name << std::endl;
		return 1;
	}

	std::wcout << L"Module base address: 0x" << std::hex << module_base_address << std::endl;

	SIZE_T size = 1024;
	LPVOID memory_to_read = handler.allocate_memory(size);
	if (!memory_to_read) {
		std::wcout << L"Failed to allocate memory" << std::endl;
		return 1;
	}

	if (!handler.read_memory(module_base_address, memory_to_read, size)) {
		std::wcout << L"Failed to read memory" << std::endl;
		return 1;
	}

	// 对 memory_to_read 执行所需的操作

	if (!handler.write_memory(memory_to_read, module_base_address, size)) {
		std::wcout << L"Failed to write memory" << std::endl;
		return 1;
	}

	DWORD new_protect = PAGE_EXECUTE_READWRITE;
	if (!handler.change_memory_protection(module_base_address, size, new_protect)) {
		std::wcout << L"Failed to change memory protection" << std::endl;
		return 1;
	}

	return 0;
}