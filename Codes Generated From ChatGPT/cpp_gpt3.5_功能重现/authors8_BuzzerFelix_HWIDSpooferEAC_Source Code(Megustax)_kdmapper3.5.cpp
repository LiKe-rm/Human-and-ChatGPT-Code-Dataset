#include <Windows.h>
#include <cstdio>
#include <cstring>
#include <memory>

// 获取 NT 头
PIMAGE_NT_HEADERS GetNtHeaders(PVOID ImageBase) {
    auto DosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(ImageBase);
    if (DosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        return nullptr;
    }
    auto NtHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(
        reinterpret_cast<PBYTE>(ImageBase) + DosHeader->e_lfanew);
    if (NtHeaders->Signature != IMAGE_NT_SIGNATURE) {
        return nullptr;
    }
    return NtHeaders;
}

// 判断 PE 文件是否为 64 位
bool Is64Bit(PVOID ImageBase) {
    auto NtHeaders = GetNtHeaders(ImageBase);
    if (NtHeaders == nullptr) {
        return false;
    }
    return NtHeaders->FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64;
}

// 在本地进程空间中申请内存
PVOID AllocateMemory(HANDLE ProcessHandle, SIZE_T Size) {
    return VirtualAllocEx(ProcessHandle, nullptr, Size, MEM_COMMIT | MEM_RESERVE,
                          PAGE_EXECUTE_READWRITE);
}

// 在内核空间中申请内存
PVOID AllocateKernelMemory(SIZE_T Size) {
    return ExAllocatePoolWithTag(NonPagedPool, Size, 'KDM');
}

// 加载 PE 文件
PVOID LoadDriver(PVOID ImageBase, HANDLE ProcessHandle) {
    if (!Is64Bit(ImageBase)) {
        printf("Error: The driver is not a 64-bit executable.\n");
        return nullptr;
    }

    // 获取 NT 头
    auto NtHeaders = GetNtHeaders(ImageBase);
    if (NtHeaders == nullptr) {
        printf("Error: Failed to get NT headers.\n");
        return nullptr;
    }

    // 获取代码段大小
    auto SizeOfCode = NtHeaders->OptionalHeader.SizeOfCode;

    // 在本地进程空间中申请内存
    auto LocalImageBase = AllocateMemory(ProcessHandle, SizeOfCode);
    if (LocalImageBase == nullptr) {
        printf("Error: Failed to allocate memory in the local process.\n");
        return nullptr;
    }

    // 在内核空间中申请内存
    auto KernelImageBase = AllocateKernelMemory(SizeOfCode);
    if (KernelImageBase == nullptr) {
        printf("Error: Failed to allocate memory in the kernel.\n");
        VirtualFreeEx(ProcessHandle, LocalImageBase, 0, MEM_RELEASE);
        return nullptr;
    }

    // 复制 PE 文件头部数据到本地进程空间中申请的内存中
    auto SizeOfHeaders = NtHeaders->OptionalHeader.SizeOfHeaders;
    if (!WriteProcessMemory(ProcessHandle, LocalImageBase, ImageBase, SizeOfHeaders, nullptr)) {
        printf("Error: Failed to copy headers to the local process.\n");
        ExFreePool(KernelImageBase);
        VirtualFreeEx(ProcessHandle, LocalImageBase, 0, MEM_RELEASE);
        return nullptr;
    }

    // 复制代码段等数据到本地进程空间中申请的内存中
    auto SizeOfImage = NtHeaders->OptionalHeader.SizeOfImage;
    if (!WriteProcessMemory(ProcessHandle, LocalImageBase, ImageBase, SizeOfImage, nullptr)) {
        printf("Error: Failed to copy image to the local process.\n");
        ExFreePool(KernelImageBase);
        VirtualFreeEx(ProcessHandle, LocalImageBase, 0, MEM_RELEASE);
        return nullptr;
    }

    // 解析重定位表并修正地址
    if (!RelocateImageByDelta(LocalImageBase, KernelImageBase)) {
        printf("Error: Failed to relocate image.\n");
        ExFreePool(KernelImageBase);
        VirtualFreeEx(ProcessHandle, LocalImageBase, 0, MEM_RELEASE);
        return nullptr;
    }

    // 解析导入表并进行函数地址重定向
    if (!ResolveImports(LocalImageBase, KernelImageBase)) {
        printf("Error: Failed to resolve imports.\n");
        ExFreePool(KernelImageBase);
        VirtualFreeEx(ProcessHandle, LocalImageBase, 0, MEM_RELEASE);
        return nullptr;
    }

    // 将本地进程空间中申请的内存中的数据写入到内核空间中申请的内存中
    if (!WriteKernelMemory(KernelImageBase, LocalImageBase, SizeOfImage)) {
        printf("Error: Failed to write image to the kernel.\n");
        ExFreePool(KernelImageBase);
        VirtualFreeEx(ProcessHandle, LocalImageBase, 0, MEM_RELEASE);
        return nullptr;
    }

    // 调用驱动的入口函数
    auto DriverEntry = reinterpret_cast<DRIVER_ENTRY*>(reinterpret_cast<PBYTE>(KernelImageBase) +
                                                       NtHeaders->OptionalHeader.AddressOfEntryPoint);
    auto Status = DriverEntry(nullptr, nullptr);
    if (!NT_SUCCESS(Status)) {
        printf("Error: Failed to call DriverEntry function.\n");
        ExFreePool(KernelImageBase);
        VirtualFreeEx(ProcessHandle, LocalImageBase, 0, MEM_RELEASE);
        return nullptr;
    }

    // 清除 PE 文件头部数据
    SecureZeroMemory(LocalImageBase, SizeOfHeaders);

    // 返回内核空间中申请的内存地址
    return KernelImageBase;
}

int main() {
    // 打开当前进程的句柄
    auto ProcessHandle = GetCurrentProcess();

    // 加载驱动文件
    auto DriverPath = "C:\\Windows\\System32\\drivers\\MyDriver.sys";
    auto DriverFile = CreateFileA(DriverPath, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING,
                                   FILE_ATTRIBUTE_NORMAL, nullptr);
    if (DriverFile == INVALID_HANDLE_VALUE) {
        printf("Error: Failed to open driver file.\n");
        return 0;
    }
    auto DriverSize = GetFileSize(DriverFile, nullptr);
    auto DriverBuffer = std::make_unique<BYTE[]>(DriverSize);
    DWORD BytesRead = 0;
    if (!ReadFile(DriverFile, DriverBuffer.get(), DriverSize, &BytesRead, nullptr)) {
        printf("Error: Failed toread driver file.\n");
        CloseHandle(DriverFile);
        return 0;
    }

    // 加载驱动
    auto DriverBase = LoadDriver(DriverBuffer.get(), ProcessHandle);
    if (DriverBase == nullptr) {
        printf("Error: Failed to load driver.\n");
        CloseHandle(DriverFile);
        return 0;
    }

    printf("Driver loaded at address 0x%p.\n", DriverBase);

    // 关闭文件句柄并退出程序
    CloseHandle(DriverFile);
    return 0;
}