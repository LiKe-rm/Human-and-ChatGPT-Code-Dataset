#ifndef _CDCACM_H_
#define _CDCACM_H_

#include <Arduino.h>
#include <USBHost_t36.h>

class CDCACM {
public:
    CDCACM(USBHost &host);

    bool Init(uint8_t parent, uint8_t port, bool lowspeed);
    void Task();
    bool RcvData(uint16_t *bytes_rcvd, uint8_t *dataptr);
    bool SndData(uint16_t bytes_snd, uint8_t *dataptr);
    bool SetCommFeature(uint16_t featureSelector, uint16_t data);
    bool GetCommFeature(uint16_t featureSelector, uint16_t *data);
    bool ClearCommFeature(uint16_t featureSelector);
    bool SetLineCoding(const CDC_LINE_CODING *lineCoding);
    bool GetLineCoding(CDC_LINE_CODING *lineCoding);
    bool SetControlLineState(uint8_t signalBitmap);
    bool SendBreak(uint16_t duration);

protected:
    USBHost *_host;
    uint8_t _dev_addr;
    uint8_t _if_control;
    uint8_t _if_data;
    uint8_t _ep_in;
    uint8_t _ep_out;
    uint8_t _ep_int;
    bool _device_available;
    bool _cdc_initialized;

    void EndpointXtract(uint8_t conf, uint8_t iface, uint8_t alt, uint8_t proto, const USB_ENDPOINT_DESCRIPTOR *ep);
};

#endif // _CDCACM_H_

#include "cdcacm.h"

CDCACM::CDCACM(USBHost &host) {
    _host = &host;
    _device_available = false;
    _cdc_initialized = false;
}

bool CDCACM::Init(uint8_t parent, uint8_t port, bool lowspeed) {
    // Initialize the CDC device
    // ...

    _host->DriverDefaults(_if_control, _dev_addr);
    _host->DriverDefaults(_if_data, _dev_addr);
    _host->RegisterDriver(_if_control, this);
    _host->RegisterDriver(_if_data, this);
    _host->SetConfiguration(_dev_addr, 1);

    // Retrieve device descriptor and configuration descriptor
    // ...

    // Extract endpoints information
    // ...

    // Initialize CDC device (SetLineCoding, SetControlLineState)
    // ...

    _cdc_initialized = true;
    return true;
}

void CDCACM::Task() {
    if (!_cdc_initialized) return;
    // CDC device tasks, such as handling received data
    // ...
}

bool CDCACM::RcvData(uint16_t *bytes_rcvd, uint8_t *dataptr) {
    // Receive data from the CDC device
    // ...
}

bool CDCACM::SndData(uint16_t bytes_snd, uint8_t *dataptr) {
    // Send data to the CDC device
    // ...
}

bool CDCACM::SetCommFeature(uint16_t featureSelector, uint16_t data) {
    // Set the specified communication feature
    // ...
}

bool CDCACM::GetCommFeature(uint16_t featureSelector, uint16_t *data) {
    // Get the specified communication feature
    // ...
}

bool CDCACM::ClearCommFeature(uint16_t featureSelector) {
    // Clear the specified communication feature
    // ...
}

bool CDCACM::SetLineCoding(const CDC_LINE_CODING *lineCoding) {
    // Set the line coding (data format)
     // ...
}  
