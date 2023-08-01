#include <windows.h>
#include <bluetoothapis.h>
#include <iostream>
#include <vector>
#include <string>

#define DISCOVERY_TIME_SECONDS 30

class BluetoothTest {
    HANDLE radio;
    BLUETOOTH_FIND_RADIO_PARAMS radioParam;
    BLUETOOTH_RADIO_INFO radioInfo;
    BLUETOOTH_DEVICE_SEARCH_PARAMS deviceSearchParams;
    BLUETOOTH_DEVICE_INFO deviceInfo;
    std::vector<std::string> mDevicesList;
    int index = 0;

public:
    BluetoothTest() {
        radioParam.dwSize = sizeof(BLUETOOTH_FIND_RADIO_PARAMS);
        radioInfo.dwSize = sizeof(BLUETOOTH_RADIO_INFO);
        deviceSearchParams.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
        deviceInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
    }

    void initBt() {
        HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio(&radioParam, &radio);
        if (hFind == NULL) {
            std::cout << "No Bluetooth radios found\n";
            return;
        }
        doDiscovery();
    }

    void doDiscovery() {
        deviceSearchParams.fReturnAuthenticated = TRUE;
        deviceSearchParams.fReturnRemembered = TRUE;
        deviceSearchParams.fReturnUnknown = TRUE;
        deviceSearchParams.fReturnConnected = TRUE;
        deviceSearchParams.fIssueInquiry = TRUE;
        deviceSearchParams.cTimeoutMultiplier = DISCOVERY_TIME_SECONDS;

        HBLUETOOTH_DEVICE_FIND hDevFind = BluetoothFindFirstDevice(&deviceSearchParams, &deviceInfo);
        if (hDevFind == NULL) {
            std::cout << "No Bluetooth devices found\n";
            return;
        }

        do {
            char deviceName[248];
            WideCharToMultiByte(CP_ACP, 0, deviceInfo.szName, -1, deviceName, sizeof(deviceName), NULL, NULL);
            std::string btinfo = std::string(deviceName) + " : " + std::to_string(deviceInfo.Address.ullLong);
            if (std::find(mDevicesList.begin(), mDevicesList.end(), btinfo) == mDevicesList.end()) {
                mDevicesList.push_back(btinfo);
                index++;
                std::cout << "Device found: " << btinfo << "\n";
            }

        } while (BluetoothFindNextDevice(hDevFind, &deviceInfo));

        BluetoothFindDeviceClose(hDevFind);
    }
    
    void tearDown() {
        BluetoothFindRadioClose(radio);
    }
};

int main() {
    BluetoothTest btTest;
    btTest.initBt();
    btTest.tearDown();
    return 0;
}
