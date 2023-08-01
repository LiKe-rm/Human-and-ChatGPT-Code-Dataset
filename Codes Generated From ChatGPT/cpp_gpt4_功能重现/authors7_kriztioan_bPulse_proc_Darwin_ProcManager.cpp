#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <unistd.h>

#include <mach/mach.h>
#include <mach/mach_host.h>
#include <mach/processor_info.h>
#include <mach/vm_statistics.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <net/route.h>
#include <netinet/in.h>
#include <libproc.h>

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/ps/IOPSKeys.h>
#include <IOKit/ps/IOPowerSources.h>
#include <IOKit/IOBSD.h>

class MacOSProcessManager {
public:
    MacOSProcessManager() {
        updateProcessorInfo();
        updateMemoryInfo();
        updateNetworkInfo();
        updateDiskInfo();
    }

    double getCpuUsage() {
        return cpuUsage;
    }

    uint64_t getMemoryUsage() {
        return memoryUsage;
    }

    uint64_t getTotalMemory() {
        return totalMemory;
    }

    uint64_t getFreeMemory() {
        return freeMemory;
    }

    uint64_t getNetworkReceivedBytes() {
        return networkReceivedBytes;
    }

    uint64_t getNetworkSentBytes() {
        return networkSentBytes;
    }

    uint64_t getDiskUsedSpace() {
        return diskUsedSpace;
    }

    uint64_t getDiskTotalSpace() {
        return diskTotalSpace;
    }

    uint64_t getDiskFreeSpace() {
        return diskFreeSpace;
    }

    void updateProcessorInfo() {
        processor_cpu_load_info_t cpuLoadInfo;
        mach_msg_type_number_t msgTypeNumber;
        natural_t processorCount;

        kern_return_t kr = host_processor_info(mach_host_self(),
                                               PROCESSOR_CPU_LOAD_INFO,
                                               &processorCount,
                                               (processor_info_array_t *)&cpuLoadInfo,
                                               &msgTypeNumber);

        if (kr != KERN_SUCCESS) {
            throw std::runtime_error("Failed to get processor info");
        }

        double totalSystemTime = 0;
        double totalUserTime = 0;
        double totalIdleTime = 0;

        for (natural_t i = 0; i < processorCount; i++) {
            totalSystemTime += cpuLoadInfo[i].cpu_ticks[CPU_STATE_SYSTEM];
            totalUserTime += cpuLoadInfo[i].cpu_ticks[CPU_STATE_USER] + cpuLoadInfo[i].cpu_ticks[CPU_STATE_NICE];
            totalIdleTime += cpuLoadInfo[i].cpu_ticks[CPU_STATE_IDLE];
        }

        double totalTicks = totalSystemTime + totalUserTime + totalIdleTime;
        cpuUsage = 100.0 * (totalSystemTime + totalUserTime) / totalTicks;

        vm_deallocate(mach_task_self(), (vm_address_t)cpuLoadInfo, msgTypeNumber);
    }

    void updateMemoryInfo() {
        vm_size_t pageSize;
        mach_port_t machPort;
        mach_msg_type_number_t count;
        vm_statistics64_data_t vmStats;
        machPort = mach_host_self();
        count = sizeof(vmStats) / sizeof(natural_t);
        if (KERN_SUCCESS == host_page_size(machPort, &pageSize) &&
            KERN_SUCCESS == host_statistics64(machPort, HOST_VM_INFO,
                                              (host_info64_t)&vmStats, &count)) {
            totalMemory = (uint64_t)vmStats.wire_count * (uint64_t)pageSize;
            freeMemory = (uint64_t)vmStats.free_count * (uint64_t)pageSize;
            memoryUsage = totalMemory - freeMemory;
        } else {
            throw std::runtime_error("Failed to get memory info");
        }
    }

    void updateNetworkInfo() {
        int mib[] = { CTL_NET, AF_ROUTE, 0, 0, NET_RT_IFLIST, 0 };
        size_t len;
        if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
            throw std::runtime_error("Failed to get network info");
        }

        char *buf = new char[len];
        if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
            throw std::runtime_error("Failed to get network info");
        }

        char *lim = buf + len;
        char *next = NULL;
        networkReceivedBytes = 0;
        networkSentBytes = 0;

        for (char *ptr = buf; ptr < lim; ptr = next) {
            struct if_msghdr *ifm = reinterpret_cast<struct if_msghdr *>(ptr);
            next = ptr + ifm->ifm_msglen;
            if (ifm->ifm_type == RTM_IFINFO) {
                struct sockaddr_dl *sdl = reinterpret_cast<struct sockaddr_dl *>(ifm + 1);
                if (sdl->sdl_type == IFT_ETHER) {
                    networkReceivedBytes += ifm->ifm_data.ifi_ibytes;
                    networkSentBytes += ifm->ifm_data.ifi_obytes;
                }
            }
        }

        delete[] buf;
    }

    void updateDiskInfo() {
        io_iterator_t it;
        io_registry_entry_t disk;

        kern_return_t kr = IOServiceGetMatchingServices(kIOMasterPortDefault,
                                                        IOServiceMatching(kIOMediaClass),
                                                        &it);

        if (kr != KERN_SUCCESS) {
            throw std::runtime_error("Failed to get disk info");
        }

        diskUsedSpace = 0;
        diskTotalSpace = 0;
        diskFreeSpace = 0;

        while ((disk = IOIteratorNext(it))) {
            CFNumberRef blockSizeRef, blockCountRef;
            uint64_t blockSize, blockCount;

            blockSizeRef = (CFNumberRef)IORegistryEntryCreateCFProperty(disk, CFSTR(kIOMediaPreferredBlockSizeKey), kCFAllocatorDefault, 0);
            blockCountRef = (CFNumberRef)IORegistryEntryCreateCFProperty(disk, CFSTR(kIOMediaSizeKey), kCFAllocatorDefault, 0);

            if (blockSizeRef && blockCountRef) {
                CFNumberGetValue(blockSizeRef, kCFNumberLongLongType, &blockSize);
                CFNumberGetValue(blockCountRef, kCFNumberLongLongType, &blockCount);

                uint64_t size = blockSize * blockCount;

                if (IOObjectConformsTo(disk, kIOMediaClass) && !IORegistryEntryGetChildEntry(disk, kIOServicePlane)) {
                    diskTotalSpace += size;
                    diskUsedSpace += size;

                    CFBooleanRef isWritable = (CFBooleanRef)IORegistryEntryCreateCFProperty(disk, CFSTR(kIOMediaWritableKey), kCFAllocatorDefault, 0);
                    if (isWritable && CFBooleanGetValue(isWritable)) {
                        CFTypeRef bsdName = IORegistryEntrySearchCFProperty(disk, kIOServicePlane, CFSTR(kIOBSDNameKey), kCFAllocatorDefault, kIORegistryIterateRecursively);
                        if (bsdName) {
                            std::string bsdNameStr("disk");
                            const char *bsdNameCString = CFStringGetCStringPtr((CFStringRef)bsdName, kCFStringEncodingASCII);
                            if (bsdNameCString) {
                                bsdNameStr = bsdNameCString;
                            }
                            CFRelease(bsdName);

                            struct statfs stat;
                            std::string mountPoint("/dev/");
                            mountPoint += bsdNameStr;
                            if (statfs(mountPoint.c_str(), &stat) == 0) {
                                diskUsedSpace -= stat.f_bfree * stat.f_bsize;
                            }
                        }
                    }
                    if (isWritable) {
                        CFRelease(isWritable);
                    }
                }
            }

            if (blockSizeRef) {
                CFRelease(blockSizeRef);
            }
            if (blockCountRef) {
                CFRelease(blockCountRef);
            }

            IOObjectRelease(disk);
        }

        IOObjectRelease(it);
        diskFreeSpace = diskTotalSpace - diskUsedSpace;
    }

private:
    double cpuUsage;
    uint64_t memoryUsage;
    uint64_t totalMemory;
    uint64_t freeMemory;
    uint64_t networkReceivedBytes;
    uint64_t networkSentBytes;
    uint64_t diskUsedSpace;
    uint64_t diskTotalSpace;
    uint64_t diskFreeSpace;
};


