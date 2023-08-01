#include <iostream>
#include <Windows.h>
#include <Softpub.h>
#include <wincrypt.h>
#include <wintrust.h>

#pragma comment(lib, "wintrust.lib")

int main()
{
    // 获取驱动程序路径
    std::wstring driverPath = L"C:\\Windows\\System32\\drivers\\xxx.sys";

    // 初始化WINTRUST_DATA结构体
    WINTRUST_FILE_INFO fileInfo = { 0 };
    fileInfo.cbStruct = sizeof(fileInfo);
    fileInfo.pcwszFilePath = driverPath.c_str();
    fileInfo.hFile = NULL;
    fileInfo.pgKnownSubject = NULL;

    WINTRUST_DATA wintrustData = { 0 };
    wintrustData.cbStruct = sizeof(wintrustData);
    wintrustData.pPolicyCallbackData = NULL;
    wintrustData.pSIPClientData = NULL;
    wintrustData.dwUIChoice = WTD_UI_NONE;
    wintrustData.fdwRevocationChecks = WTD_REVOKE_NONE;
    wintrustData.dwUnionChoice = WTD_CHOICE_FILE;
    wintrustData.dwStateAction = WTD_STATEACTION_VERIFY;
    wintrustData.hWVTStateData = NULL;
    wintrustData.pwszURLReference = NULL;
    wintrustData.dwProvFlags = WTD_CACHE_ONLY_URL_RETRIEVAL;
    wintrustData.dwUIContext = 0;
    wintrustData.pFile = &fileInfo;

    // 获取函数指针
    GUID guidAction = WINTRUST_ACTION_GENERIC_VERIFY_V2;
    HMODULE hWinTrust = LoadLibrary(L"wintrust.dll");
    if (hWinTrust == NULL)
    {
        std::cout << "Failed to load wintrust.dll" << std::endl;
        return 1;
    }

    PWinVerifyTrust WinVerifyTrust = (PWinVerifyTrust)GetProcAddress(hWinTrust, "WinVerifyTrust");
    if (WinVerifyTrust == NULL)
    {
        std::cout << "Failed to get function pointer" << std::endl;
        FreeLibrary(hWinTrust);
        return 1;
    }

    // 验证签名
    LONG result = WinVerifyTrust(NULL, &guidAction, &wintrustData);
    if (result != ERROR_SUCCESS)
    {
        std::cout << "The driver is not signed or the signature is invalid" << std::endl;
        FreeLibrary(hWinTrust);
        return 1;
    }

    std::cout << "The driver signature is valid" << std::endl;

    FreeLibrary(hWinTrust);
    return 0;
}