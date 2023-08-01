#include <iostream>
#include <Windows.h>
#include <winternl.h>

typedef NTSTATUS(NTAPI* NtCreateSectionPtr)(
    OUT PHANDLE SectionHandle,
    IN ULONG DesiredAccess,
    IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
    IN PLARGE_INTEGER MaximumSize,
    IN ULONG SectionPageProtection,
    IN ULONG AllocationAttributes,
    IN HANDLE FileHandle OPTIONAL
);

typedef NTSTATUS(NTAPI* NtMapViewOfSectionPtr)(
    IN HANDLE SectionHandle,
    IN HANDLE ProcessHandle,
    IN OUT PVOID* BaseAddress,
    IN ULONG_PTR ZeroBits,
    IN SIZE_T CommitSize,
    IN OUT PLARGE_INTEGER SectionOffset OPTIONAL,
    IN OUT PSIZE_T ViewSize,
    IN SECTION_INHERIT InheritDisposition,
    IN ULONG AllocationType,
    IN ULONG Win32Protect
);

bool AllocateMemoryWithVirtualAllocEx(HANDLE processHandle, PVOID* buffer, SIZE_T bufferSize, DWORD protection);
bool AllocateMemoryWithNtCreateSection(HANDLE processHandle, PVOID* buffer, SIZE_T bufferSize, DWORD protection);
bool AllocateMemoryWithFileMapping(HANDLE processHandle, PVOID* buffer, SIZE_T bufferSize, DWORD protection);
PVOID AllocateMemory(HANDLE processHandle, PVOID buffer, SIZE_T bufferSize, DWORD protection, int allocationType);

int main() {
    HANDLE processHandle = GetCurrentProcess();
    SIZE_T bufferSize = 1024;
    DWORD protection = PAGE_EXECUTE_READWRITE;
    int allocationType = 1;

    PVOID buffer = nullptr;
    PVOID allocatedMemory = AllocateMemory(processHandle, buffer, bufferSize, protection, allocationType);

    if (allocatedMemory != nullptr) {
        std::cout << "Memory allocated at: " << allocatedMemory << std::endl;
    } else {
        std::cout << "Memory allocation failed." << std::endl;
    }

    return 0;
}

PVOID AllocateMemory(HANDLE processHandle, PVOID buffer, SIZE_T bufferSize, DWORD protection, int allocationType) {
    PVOID allocatedMemory = nullptr;
    switch (allocationType) {
    case 1:
        if (AllocateMemoryWithVirtualAllocEx(processHandle, &buffer, bufferSize, protection)) {
            allocatedMemory = buffer;
        }
        break;
    case 2:
        if (AllocateMemoryWithNtCreateSection(processHandle, &buffer, bufferSize, protection)) {
            allocatedMemory = buffer;
        }
        break;
    case 3:
        if (AllocateMemoryWithFileMapping(processHandle, &buffer, bufferSize, protection)) {
            allocatedMemory = buffer;
        }
        break;
    default:
        break;
    }

    return allocatedMemory;
}

bool AllocateMemoryWithVirtualAllocEx(HANDLE processHandle, PVOID* buffer, SIZE_T bufferSize, DWORD protection) {
    *buffer = VirtualAllocEx(processHandle, nullptr, bufferSize, MEM_COMMIT | MEM_RESERVE, protection);
    return *buffer != nullptr;
}

bool AllocateMemoryWithNtCreateSection(HANDLE processHandle, PVOID* buffer, SIZE_T bufferSize, DWORD protection) {
    NtCreateSectionPtr NtCreateSection = reinterpret_cast<NtCreateSectionPtr>(GetProcAddress(GetModuleHandle(L"ntdll"), "NtCreateSection"));
    NtMapViewOfSectionPtr NtMapViewOfSection = reinterpret_cast<NtMapViewOfSectionPtr>(GetProcAddress(GetModuleHandle(L"ntdll"), "NtMapViewOfSection"));

    if (NtCreateSection == nullptr || NtMapViewOfSection == nullptr) {
        return false;
    }

    HANDLE sectionHandle;
    LARGE_INTEGER maxSize;
    maxSize.QuadPart = bufferSize;

    NTSTATUS status = NtCreateSection(&sectionHandle, SECTION_ALL_ACCESS, nullptr, &maxSize, protection, SEC_COMMIT, nullptr);
    if (status != STATUS_SUCCESS) {
        return false;
    }
    PVOID baseAddress = nullptr;
    SIZE_T viewSize = bufferSize;
    status = NtMapViewOfSection(sectionHandle, processHandle, &baseAddress, 0, 0, nullptr, &viewSize, ViewShare, 0, protection);

    if (status != STATUS_SUCCESS) {
        CloseHandle(sectionHandle);
        return false;
    }

    *buffer = baseAddress;
    CloseHandle(sectionHandle);
    return true;
}
bool AllocateMemoryWithFileMapping(HANDLE processHandle, PVOID* buffer, SIZE_T bufferSize, DWORD protection) {
    HANDLE fileMapping = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_EXECUTE_READWRITE | SEC_COMMIT, 0, bufferSize, nullptr);
    if (fileMapping == nullptr) {
        return false;
    }

    *buffer = MapViewOfFileEx(fileMapping, FILE_MAP_ALL_ACCESS, 0, 0, bufferSize, nullptr);
    if (*buffer == nullptr) {
        CloseHandle(fileMapping);
        return false;
    }

    CloseHandle(fileMapping);
    return true;
}


