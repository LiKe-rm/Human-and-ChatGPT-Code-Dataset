// vld_api.h
#pragma once
#include <windows.h>

#ifdef VLD_EXPORTS
#define VLD_API __declspec(dllexport)
#else
#define VLD_API __declspec(dllimport)
#endif

extern "C" {
    VLD_API void VLDEnable();
    VLD_API void VLDDisable();
    VLD_API void VLDReportLeaks();
}

// vld_api.cpp
#include "vld_api.h"
#include "VisualLeakDetector.h"

void VLDEnable()
{
    VisualLeakDetector::GetInstance().Enable();
}

void VLDDisable()
{
    VisualLeakDetector::GetInstance().Disable();
}

void VLDReportLeaks()
{
    VisualLeakDetector::GetInstance().ReportLeaks();
}

// VisualLeakDetector.h
#pragma once
#include <windows.h>
#include <mutex>
#include <unordered_map>

class VisualLeakDetector
{
public:
    static VisualLeakDetector& GetInstance();
    
    void Enable();
    void Disable();
    void ReportLeaks();

private:
    VisualLeakDetector();
    ~VisualLeakDetector();

    VisualLeakDetector(const VisualLeakDetector&) = delete;
    VisualLeakDetector& operator=(const VisualLeakDetector&) = delete;

    void InstallHooks();
    void UninstallHooks();

    static void* __cdecl operator new(size_t size);
    static void __cdecl operator delete(void* p);

    bool m_enabled;
    std::mutex m_mutex;
    std::unordered_map<void*, size_t> m_allocations;
};

// VisualLeakDetector.cpp
#include "VisualLeakDetector.h"
#include <iostream>

VisualLeakDetector& VisualLeakDetector::GetInstance()
{
    static VisualLeakDetector instance;
    return instance;
}

VisualLeakDetector::VisualLeakDetector()
    : m_enabled(true)
{
    InstallHooks();
}

VisualLeakDetector::~VisualLeakDetector()
{
    UninstallHooks();
    ReportLeaks();
}

void VisualLeakDetector::Enable()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_enabled = true;
}

void VisualLeakDetector::Disable()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_enabled = false;
}

void VisualLeakDetector::ReportLeaks()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if (!m_allocations.empty())
    {
        std::cerr << "Visual Leak Detector detected memory leaks!\n";
        for (const auto& alloc : m_allocations)
        {
            std::cerr << "Leaked " << alloc.second << " bytes at address " << alloc.first << '\n';
        }
    }
    else
    {
        std::cout << "Visual Leak Detector: No memory leaks detected.\n";
    }
}

void VisualLeakDetector::InstallHooks()
{
    // TODO: Implement hook installation for memory allocation and deallocation functions.
}

void VisualLeakDetector::UninstallHooks()
{
    // TODO: Implement hook removal for memory allocation and deallocation functions.
}

void* VisualLeakDetector::operator new(size_t size)
{
    void* p = malloc(size);
    if (p)
    {
        std::unique_lock<std::mutex> lock(GetInstance().m_mutex);
        if (GetInstance().m_enabled)
        {
            GetInstance().m_allocations[p] = size;
        }
    }
    return p;
}

void VisualLeakDetector::operator delete(void* p)
{
    if (p)
    {
        std::unique_lock<std::mutex> lock(GetInstance().m_mutex);
        GetInstance().m_allocations.erase(p);
    }
    free(p);
}
