#include <iostream>
#include <Windows.h>
#include <WsmAuto.h>
#include <atlbase.h>
#include <atlcom.h>

using namespace std;

class WinRMClient {
public:
    WinRMClient(const wchar_t* hostname, const wchar_t* username, const wchar_t* password);
    ~WinRMClient();
    HRESULT Setup();
    HRESULT Execute(const wchar_t* command);
    HRESULT Cleanup();

private:
    HRESULT LoadWsmSvc();
    HRESULT InitializeWinRMAPI();
    HRESULT CreateSession();
    HRESULT SetSessionOptions();
    HRESULT CreateShell();
    HRESULT RunCommand(const wchar_t* command);
    HRESULT ReceiveOutput();
    HRESULT WaitForAsyncCompletion();
    HRESULT ReleaseResources();

    CComPtr<IWSMan> pWSMan;
    CComPtr<IWSManSession> pSession;
    CComPtr<IWSManShell> pShell;
    CComPtr<IWSManCommand> pCommand;
    CComPtr<IWSManAsyncResult> pAsyncResult;
    HANDLE hCompletionEvent;

    wstring hostname;
    wstring username;
    wstring password;
};

WinRMClient::WinRMClient(const wchar_t* hostname, const wchar_t* username, const wchar_t* password)
    : hostname(hostname), username(username), password(password), hCompletionEvent(NULL) {
}

WinRMClient::~WinRMClient() {
    Cleanup();
}

HRESULT WinRMClient::Setup() {
    HRESULT hr = LoadWsmSvc();
    if (FAILED(hr)) {
        return hr;
    }

    hr = InitializeWinRMAPI();
    if (FAILED(hr)) {
        return hr;
    }

    hr = CreateSession();
    if (FAILED(hr)) {
        return hr;
    }

    hr = SetSessionOptions();
    if (FAILED(hr)) {
        return hr;
    }

    hr = CreateShell();
    if (FAILED(hr)) {
        return hr;
    }

    return S_OK;
}

HRESULT WinRMClient::Execute(const wchar_t* command) {
    HRESULT hr = RunCommand(command);
    if (FAILED(hr)) {
        return hr;
    }

    hr = ReceiveOutput();
    if (FAILED(hr)) {
        return hr;
    }

    return S_OK;
}

HRESULT WinRMClient::Cleanup() {
    ReleaseResources();
    if (hCompletionEvent) {
        CloseHandle(hCompletionEvent);
        hCompletionEvent = NULL;
    }

    return S_OK;
}

HRESULT WinRMClient::LoadWsmSvc() {
    return CoLoadLibrary(L"WsmSvc.dll", TRUE);
}

HRESULT WinRMClient::InitializeWinRMAPI() {
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        return hr;
    }

    hr = pWSMan.CoCreateInstance(__uuidof(WSMan));
    if (FAILED(hr)) {
        CoUninitialize();
        return hr;
    }

    return S_OK;
}

HRESULT WinRMClient::CreateSession() {
    CComBSTR connection_str = (L"http://" + hostname + L":5985/wsman").c_str();
    CComBSTR auth_scheme = L"Basic";
    CComBSTR user_token = (username + L":" + password).c_str();

    pSession = pWSMan->CreateSession(connection_str, WSManFlagCredUsernamePassword, auth_scheme, user_token, NULL);
    if (!pSession) {
        return E_FAIL;
    }

    return S_OK;
}

HRESULT WinRMClient::SetSessionOptions() {
    CComVariant option_val;
    option_val = L"en-US";
    pSession->SetOption(WSManOptionLocale, option_val);

    option_val = L"application/soap+xml;charset=UTF-8";
    pSession->SetOption(WSManOptionContentType, option_val);

    option_val.Clear();
    option_val = 15000; // 15 seconds timeout
    pSession->SetOption(WSManOptionTimeout, option_val);

    return S_OK;
}

HRESULT WinRMClient::CreateShell() {
    pShell = pSession->CreateShell(NULL, NULL, NULL);
    if (!pShell) {
        return E_FAIL;
    }

    return S_OK;
}

HRESULT WinRMClient::RunCommand(const wchar_t* command) {
    CComBSTR cmd = command;
    pCommand = pShell->Run(cmd, NULL);
    if (!pCommand) {
        return E_FAIL;
    }

    return S_OK;
}

HRESULT WinRMClient::ReceiveOutput() {
    hCompletionEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!hCompletionEvent) {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    pAsyncResult = pCommand->Receive(NULL);
    if (!pAsyncResult) {
        return E_FAIL;
    }

    pAsyncResult->SetOnCompleteCallback(this, &WinRMClient::WaitForAsyncCompletion);

    return WaitForAsyncCompletion();
}

HRESULT WinRMClient::WaitForAsyncCompletion() {
    DWORD result = WaitForSingleObject(hCompletionEvent, INFINITE);
    if (result != WAIT_OBJECT_0) {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    CComPtr<IWSManEnumerator> pOutput = pAsyncResult->Result();
    if (!pOutput) {
        return E_FAIL;
    }

    while (true) {
        CComPtr<IWSManEx> pWSManEx;
        pWSMan->QueryInterface(IID_PPV_ARGS(&pWSManEx));
        CComBSTR output_xml = pWSManEx->XmlFragment(pOutput->ReadItem());
        if (output_xml.Length() == 0) {
            break;
        }

        wcout << output_xml << endl;
    }

    return S_OK;
}

HRESULT WinRMClient::ReleaseResources() {
    pAsyncResult.Release();
    pCommand.Release();
    pShell.Release();
    pSession.Release();
    pWSMan.Release();

    return S_OK;
}

int wmain(int argc, wchar_t* argv[]) {
    if (argc != 5) {
        wcout << L"Usage: WinRMClient <hostname> <username> <password> <command>" << endl;
        return 1;
    }

    WinRMClient client(argv[1], argv[2], argv[3]);

    HRESULT hr = client.Setup();
    if (FAILED(hr)) {
        wcout << L"Failed to setup WinRM client: " << hr << endl;
        return 1;
    }

    hr = client.Execute(argv[4]);
    if (FAILED(hr)) {
        wcout << L"Failed to execute command: " << hr << endl;
        return 1;
    }

    client.Cleanup();

    return 0;
}

