#include <iostream>
#include <string>
#include <windows.h>
#include <wininet.h>

#pragma comment(lib, "wininet.lib")

class ProxySettings {
public:
    bool QueryHttpVersion();
    bool QueryProxySettings();
    bool SetProxySettings();
    void PrintProxySettings();

private:
    std::string httpVersion;
    std::string proxyServer;
    std::string proxyBypass;
    std::string autoConfigUrl;
    DWORD accessType;
};

bool ProxySettings::QueryHttpVersion() {
    HINTERNET hInternet = InternetOpen("UserAgent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) {
        return false;
    }

    char version[32] = {0};
    DWORD versionSize = sizeof(version);
    if (!InternetQueryOption(hInternet, INTERNET_OPTION_VERSION, &version, &versionSize)) {
        InternetCloseHandle(hInternet);
        return false;
    }
    InternetCloseHandle(hInternet);
    httpVersion = version;
    return true;
}

bool ProxySettings::QueryProxySettings() {
    HINTERNET hInternet = InternetOpen("UserAgent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) {
        return false;
    }

    INTERNET_PROXY_INFO proxyInfo;
    DWORD proxyInfoSize = sizeof(proxyInfo);
    if (!InternetQueryOption(hInternet, INTERNET_OPTION_PROXY, &proxyInfo, &proxyInfoSize)) {
        InternetCloseHandle(hInternet);
        return false;
    }
    InternetCloseHandle(hInternet);

    accessType = proxyInfo.dwAccessType;
    proxyServer = proxyInfo.lpszProxy;
    proxyBypass = proxyInfo.lpszProxyBypass;
    autoConfigUrl = proxyInfo.lpszAutoConfigUrl;

    return true;
}

bool ProxySettings::SetProxySettings() {
    HINTERNET hInternet = InternetOpen("UserAgent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) {
        return false;
    }

    INTERNET_PROXY_INFO proxyInfo;
    proxyInfo.dwAccessType = accessType;
    proxyInfo.lpszProxy = const_cast<char*>(proxyServer.c_str());
    proxyInfo.lpszProxyBypass = const_cast<char*>(proxyBypass.c_str());
    proxyInfo.lpszAutoConfigUrl = const_cast<char*>(autoConfigUrl.c_str());

    if (!InternetSetOption(hInternet, INTERNET_OPTION_PROXY, &proxyInfo, sizeof(proxyInfo))) {
        InternetCloseHandle(hInternet);
        return false;
    }
    InternetCloseHandle(hInternet);
    return true;
}

void ProxySettings::PrintProxySettings() {
    std::cout << "HTTP Version: " << httpVersion << std::endl;
    std::cout << "Access Type: " << accessType << std::endl;
    std::cout << "Proxy Server: " << proxyServer << std::endl;
    std::cout << "Proxy Bypass: " << proxyBypass << std::endl;
    std::cout << "Auto Config URL: " << autoConfigUrl << std::endl;
}

int main() {
    ProxySettings proxySettings;

    if (proxySettings.QueryHttpVersion()) {
        if (proxySettings.QueryProxySettings()) {
            proxySettings.PrintProxySettings();
            // 修改代理设置
            // proxySettings.SetProxySettings();
        } else {
            std::cout << "Failed to query proxy settings." << std::endl;
        }
    } else {
        std::cout << "Failed to query HTTP version." << std::endl;
    }

    return 0;
}
