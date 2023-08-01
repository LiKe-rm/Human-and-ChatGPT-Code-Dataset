#include "main_proc.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <TlHelp32.h>

using namespace std;

DWORD FindProcessId(const std::wstring& processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshotHandle == INVALID_HANDLE_VALUE) {
        return 0;
    }

    if (Process32First(snapshotHandle, &processInfo)) {
        do {
            if (!_wcsicmp(processInfo.szExeFile, processName.c_str())) {
                CloseHandle(snapshotHandle);
                return processInfo.th32ProcessID;
            }
        } while (Process32Next(snapshotHandle, &processInfo));
    }

    CloseHandle(snapshotHandle);
    return 0;
}

int main()
{
    cout << "Suspending Alkad AntiCheat..." << endl;

    DWORD processId = FindProcessId(L"Alkad.exe");
    if (!processId) {
        cout << "Alkad.exe not found. Exiting in 5 seconds..." << endl;
        Sleep(5000);
        return 1;
    }

    SuspendProcess(processId);

    Sleep(1000);
    cout << "Successfully Suspended Alkad..." << endl;
    Sleep(4500);

    return 0;
}
