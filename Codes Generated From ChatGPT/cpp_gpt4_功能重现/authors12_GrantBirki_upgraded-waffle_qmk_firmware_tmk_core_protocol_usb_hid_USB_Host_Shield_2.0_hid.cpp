#ifndef HID_H
#define HID_H

#include <iostream>
#include <iomanip>
#include <USBHost.h>

class USBHID: public USBHost {
public:
    USBHID();
    ~USBHID();

    bool initialize();
    bool getHIDReportDescriptor();
    bool setReportProtocol(uint8_t protocol);
    bool sendReport(uint8_t *report, uint8_t reportLength);
    bool getReport(uint8_t reportId, uint8_t *report, uint8_t reportLength);

    void printHIDDescriptor();
    void printEndpointDescriptor();

private:
    USBHost usb;
    uint8_t hidInterface;
    uint8_t reportDescriptorLength;
    uint8_t *reportDescriptor;

    uint8_t inEndpointAddress;
    uint8_t outEndpointAddress;
    uint8_t inEndpointSize;
    uint8_t outEndpointSize;

    void printDescriptor(uint8_t *descriptor, uint8_t length);
};

#endif // HID_H

#include "hid.h"

USBHID::USBHID() {
}

USBHID::~USBHID() {
    if (reportDescriptor != nullptr) {
        delete[] reportDescriptor;
    }
}

bool USBHID::initialize() {
    if (!usb.begin()) {
        std::cerr << "USB Host initialization failed!" << std::endl;
        return false;
    }

    if (!usb.getHIDInterface(&hidInterface)) {
        std::cerr << "Failed to get HID interface!" << std::endl;
        return false;
    }

    if (!usb.getHIDDescriptor(hidInterface, &reportDescriptorLength)) {
        std::cerr << "Failed to get HID descriptor!" << std::endl;
        return false;
    }

    reportDescriptor = new uint8_t[reportDescriptorLength];
    if (!usb.getDescriptor(hidInterface, reportDescriptor, reportDescriptorLength)) {
        std::cerr << "Failed to get report descriptor!" << std::endl;
        return false;
    }

    if (!usb.getHIDEndpoints(hidInterface, &inEndpointAddress, &outEndpointAddress, &inEndpointSize, &outEndpointSize)) {
        std::cerr << "Failed to get HID endpoints!" << std::endl;
        return false;
    }

    return true;
}

bool USBHID::getHIDReportDescriptor() {
    return usb.getDescriptor(hidInterface, reportDescriptor, reportDescriptorLength);
}

bool USBHID::setReportProtocol(uint8_t protocol) {
    return usb.setHIDProtocol(hidInterface, protocol);
}

bool USBHID::sendReport(uint8_t *report, uint8_t reportLength) {
    return usb.controlTransfer(hidInterface, USB_REQUEST_TYPE_CLASS | USB_RECIPIENT_INTERFACE, USB_REQ_SET_REPORT, 0x200, 0, report, reportLength);
}

bool USBHID::getReport(uint8_t reportId, uint8_t *report, uint8_t reportLength) {
    return usb.controlTransfer(hidInterface, USB_REQUEST_TYPE_CLASS | USB_RECIPIENT_INTERFACE | USB_REQ_TYPE_IN, USB_REQ_GET_REPORT, 0x100 | reportId, 0, report, reportLength);
}

void USBHID::printHIDDescriptor() {
    printDescriptor(reportDescriptor, reportDescriptorLength);
}

void USBHID::printEndpointDescriptor() {
    uint8_t epDescriptor[7];
    if (usb.getEndpointDescriptor(hidInterface, inEndpointAddress, epDescriptor, sizeof(epDescriptor))) {
        std::cout << "Input Endpoint Descriptor:" << std::endl;
        printDescriptor(epDescriptor, sizeof(epDescriptor));
    } else {
        std::cerr << "Failed to get input endpoint descriptor!" << std::endl;
    }

    if (usb.getEndpointDescriptor(hidInterface, outEndpointAddress, epDescriptor, sizeof(epDescriptor))) {
        std::cout << "Output Endpoint Descriptor:" << std::endl;
        printDescriptor(epDescriptor, sizeof(epDescriptor));
    } else {
        std::cerr << "Failed to get output endpoint descriptor!" << std::endl;
    }

}

void USBHID::printDescriptor(uint8_t *descriptor, uint8_t length) {
    std::cout << std::hex << std::uppercase << std::setfill('0');
    for (uint8_t i = 0; i < length; ++i) {
        std::cout << std::setw(2) << static_cast<unsigned>(descriptor[i]) << " ";
        if ((i + 1) % 16 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::dec << std::nouppercase << std::endl;
}
