// CapsContainer.h
#include <iostream>
#include <map>
#include <vector>
#include <string>

struct rfbCapabilityInfo {
    uint32_t code;
    std::string vendor;
    std::string name;
    std::string description;
};

class CapsContainer {
public:
    CapsContainer();
    ~CapsContainer();

    void Add(uint32_t code, const std::string& vendor, const std::string& name, const std::string& description);
    void Add(const rfbCapabilityInfo& capInfo);
    const rfbCapabilityInfo* GetInfo(uint32_t code) const;
    std::string GetDescription(uint32_t code) const;
    void Enable(uint32_t code, bool enable);

    bool IsKnown(uint32_t code) const;
    bool IsEnabled(uint32_t code) const;
    const rfbCapabilityInfo* GetByOrder(size_t index) const;

private:
    std::map<uint32_t, rfbCapabilityInfo> m_caps;
    std::vector<uint32_t> m_order;
};

// CapsContainer.cpp
#include "CapsContainer.h"

CapsContainer::CapsContainer() {
}

CapsContainer::~CapsContainer() {
}

void CapsContainer::Add(uint32_t code, const std::string& vendor, const std::string& name, const std::string& description) {
    rfbCapabilityInfo capInfo;
    capInfo.code = code;
    capInfo.vendor = vendor;
    capInfo.name = name;
    capInfo.description = description;

    Add(capInfo);
}

void CapsContainer::Add(const rfbCapabilityInfo& capInfo) {
    m_caps[capInfo.code] = capInfo;
    m_order.push_back(capInfo.code);
}

const rfbCapabilityInfo* CapsContainer::GetInfo(uint32_t code) const {
    auto it = m_caps.find(code);
    if (it == m_caps.end()) {
        return nullptr;
    }
    return &it->second;
}

std::string CapsContainer::GetDescription(uint32_t code) const {
    const rfbCapabilityInfo* info = GetInfo(code);
    if (info) {
        return info->description;
    }
    return "";
}

void CapsContainer::Enable(uint32_t code, bool enable) {
    rfbCapabilityInfo* info = const_cast<rfbCapabilityInfo*>(GetInfo(code));
    if (info) {
        info->enabled = enable;
    }
}

bool CapsContainer::IsKnown(uint32_t code) const {
    return GetInfo(code) != nullptr;
}

bool CapsContainer::IsEnabled(uint32_t code) const {
    const rfbCapabilityInfo* info = GetInfo(code);
    if (info) {
        return info->enabled;
    }
    return false;
}

const rfbCapabilityInfo* CapsContainer::GetByOrder(size_t index) const {
    if (index < m_order.size()) {
        return GetInfo(m_order[index]);
    }
    return nullptr;
}

// main.cpp
#include <iostream>
#include "CapsContainer.h"

int main() {
    CapsContainer caps;

    caps.Add(1, "VNC", "CopyRect", "Supports the CopyRect encoding");
    caps.Add(2, "VNC", "Hextile", "Supports the Hextile encoding");

    std::cout << "Capabilities:" << std::endl;
    for (size_t i = 0; i < 2; ++i) {
        const rfbCapabilityInfo* info = caps.GetByOrder(i);
        if (info) {
            std::cout << "Code: " << info->code
                << ", Vendor: " << info->vendor
                << ", Name: " << info->name
                << ", Description: " << info->description << std::endl;
        }
    }

    caps.Enable(1, true);
    caps.Enable(2, true);

    if (caps.IsEnabled(1)) {
        std::cout << "Capability 1 (CopyRect) is enabled." << std::endl;
    }

    if (caps.IsEnabled(2)) {
        std::cout << "Capability 2 (Hextile) is enabled." << std::endl;
    }

    return 0;
}

