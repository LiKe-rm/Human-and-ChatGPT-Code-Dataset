#include <iostream>
#include <Windows.h>
#include <Winternl.h>
#include <map>

// 原始函数声明
typedef PVOID(NTAPI* RtlAllocateHeap_t)(PVOID, ULONG, SIZE_T);
typedef PVOID(NTAPI* RtlReAllocateHeap_t)(PVOID, ULONG, PVOID, SIZE_T);
typedef BOOLEAN(NTAPI* RtlFreeHeap_t)(PVOID, ULONG, PVOID);

// 原始函数指针
RtlAllocateHeap_t OriginalRtlAllocateHeap = nullptr;
RtlReAllocateHeap_t OriginalRtlReAllocateHeap = nullptr;
RtlFreeHeap_t OriginalRtlFreeHeap = nullptr;

// 加密函数
void EncryptMemory(PVOID memory, SIZE_T size) {
    // 这里可以实现自己的加密算法，例如异或加密
    for (SIZE_T i = 0; i < size; ++i) {
        ((PBYTE)memory)[i] ^= 0xAA; // 示例: 对内存的每个字节异或0xAA
    }
}

// Hooked 函数
PVOID NTAPI HookedRtlAllocateHeap(PVOID HeapHandle, ULONG Flags, SIZE_T Size) {
    PVOID memory = OriginalRtlAllocateHeap(HeapHandle, Flags, Size);
    if (memory) {
        EncryptMemory(memory, Size);
    }
    return memory;
}

PVOID NTAPI HookedRtlReAllocateHeap(PVOID HeapHandle, ULONG Flags, PVOID Memory, SIZE_T Size) {
    PVOID newMemory = OriginalRtlReAllocateHeap(HeapHandle, Flags, Memory, Size);
    if (newMemory) {
        EncryptMemory(newMemory, Size);
    }
    return newMemory;
}

BOOLEAN NTAPI HookedRtlFreeHeap(PVOID HeapHandle, ULONG Flags, PVOID Memory) {
    SIZE_T size = RtlSizeHeap(HeapHandle, Flags, Memory);
    EncryptMemory(Memory, size); // 在释放内存之前解密
    return OriginalRtlFreeHeap(HeapHandle, Flags, Memory);
}

// 替换函数指针
void ReplaceFunctions() {
    HMODULE ntdll = GetModuleHandle(L"ntdll.dll");
    OriginalRtlAllocateHeap = (RtlAllocateHeap_t)GetProcAddress(ntdll, "RtlAllocateHeap");
    OriginalRtlReAllocateHeap = (RtlReAllocateHeap_t)GetProcAddress(ntdll, "RtlReAllocateHeap");
    OriginalRtlFreeHeap = (RtlFreeHeap_t)GetProcAddress(ntdll, "RtlFreeHeap");

    DWORD oldProtect;
    VirtualProtect(OriginalRtlAllocateHeap, sizeof(PVOID), PAGE_EXECUTE_READWRITE, &oldProtect);
    *(PVOID*)(&OriginalRtlAllocateHeap) = &HookedRtlAllocateHeap;
    VirtualProtect(OriginalRtlAllocateHeap, sizeof(PVOID), oldProtect, &oldProtect);

    VirtualProtect(OriginalRtlReAllocateHeap, sizeof(PVOID), PAGE_EXECUTE_READWRITE, &oldProtect);
    *(PVOID*)(&OriginalRtlReAllocateHeap) = &HookedRtlReAllocateHeap;
    VirtualProtect(OriginalRtlReAllocateHeap, sizeof(PVOID), oldProtect, &oldProtect);

    VirtualProtect(OriginalRtlFreeHeap, sizeof(PVOID), PAGE_EXECUTE_READWRITE, &oldProtect);
    *(PVOID*)(&OriginalRtlFreeHeap) = &HookedRtlFreeHeap;
    VirtualProtect(OriginalRtlFreeHeap, sizeof(PVOID), oldProtect, &oldProtect);
}
