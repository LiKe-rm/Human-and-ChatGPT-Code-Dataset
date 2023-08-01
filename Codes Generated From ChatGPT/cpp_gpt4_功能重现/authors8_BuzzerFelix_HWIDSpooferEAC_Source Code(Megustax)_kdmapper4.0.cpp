#include <iostream>
#include <vector>
#include <iomanip>
#include <Windows.h>
#include "driver_mapper.hpp"
#include "pe_utils.hpp"
#include "kernel_utils.hpp"

uint64_t driver_mapper::MapDriverToKernel(HANDLE device_handle, std::vector<uint8_t> driver_image)
{
    PEHeaders pe_headers(driver_image.data());

    if (!pe_headers.IsValid())
    {
        std::cout << "Invalid PE image format" << std::endl;
        Sleep(2000);
        return 0;
    }

    const uint32_t image_size = pe_headers.GetImageSize();

    void* local_image_base = VirtualAlloc(nullptr, image_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    uint64_t kernel_image_base = kernel_utils::AllocatePool(device_handle, image_size);

    if (!kernel_image_base)
    {
        std::cout << "Failed to allocate remote image in kernel" << std::endl;
        Sleep(2000);
        return 0;
    }

    std::cout << "Image base allocated at 0x" << reinterpret_cast<void*>(kernel_image_base) << std::endl;

    // Copy PE image to local buffer
    pe_headers.CopyImageToLocalBuffer(local_image_base);

    // Relocate image and resolve imports
    pe_headers.ProcessRelocations(kernel_image_base);
    if (!pe_headers.ProcessImports(device_handle))
    {
        std::cout << "Failed to resolve imports" << std::endl;
        Sleep(2000);
        return 0;
    }

    // Write processed image to kernel
    if (!kernel_utils::WriteMemory(device_handle, kernel_image_base, local_image_base, image_size))
    {
        std::cout << "Failed to write local image to remote image" << std::endl;
        Sleep(2000);
        return 0;
    }

    VirtualFree(local_image_base, 0, MEM_RELEASE);

    // Call driver entry point
    const uint64_t driver_entry_address = kernel_image_base + pe_headers.GetEntryPoint();

    std::cout << "Calling DriverEntry at 0x" << reinterpret_cast<void*>(driver_entry_address) << std::endl;

    NTSTATUS status = 0;
    if (!kernel_utils::CallKernelFunction(device_handle, &status, driver_entry_address))
    {
        std::cout << "Failed to call driver entry" << std::endl;
        Sleep(2000);
        return 0;
    }

    std::cout << "DriverEntry returned 0x" << std::hex << std::setw(8) << std::setfill('0') << std::uppercase << status << std::nouppercase << std::dec << std::endl;

    // Erase PE headers
    kernel_utils::EraseMemory(device_handle, kernel_image_base, pe_headers.GetSizeOfHeaders());

    return kernel_image_base;
}

class PEHeaders {
public:
    PEHeaders(const uint8_t* raw_image);
    bool IsValid() const;
    uint32_t GetImageSize() const;
    uint32_t GetEntryPoint() const;
    uint32_t GetSizeOfHeaders() const;
    void CopyImageToLocalBuffer(void* local_buffer);
    void ProcessRelocations(uint64_t kernel_image_base);
    bool ProcessImports(HANDLE device_handle);

private:
    // Private methods for working with PE headers, imports, and relocations
};

namespace kernel_utils {
    uint64_t AllocatePool(HANDLE device_handle, uint32_t image_size);
    bool WriteMemory(HANDLE device_handle, uint64_t kernel_image_base, void* local_image_base, uint32_t image_size);
    bool CallKernelFunction(HANDLE device_handle, NTSTATUS* status, uint64_t function_address);
    void EraseMemory(HANDLE device_handle, uint64_t kernel_image_base, uint32_t size_of_headers);

    // Other helper functions for working with kernel modules, memory, etc.
};
