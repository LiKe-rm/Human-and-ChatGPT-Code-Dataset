#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cor.h>
#include <corhdr.h>
#include <metahost.h>
#include <atlbase.h>
#include <atlconv.h>

// 将指定的.NET模块文件读入内存
LPVOID MapFileToMemory(LPCWSTR filePath) {
    HANDLE hFile = CreateFileW(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open file: " << GetLastError() << std::endl;
        return nullptr;
    }

    DWORD fileSize = GetFileSize(hFile, NULL);
    HANDLE hFileMapping = CreateFileMappingW(hFile, NULL, PAGE_READONLY, 0, fileSize, NULL);
    if (!hFileMapping) {
        std::cerr << "Failed to create file mapping: " << GetLastError() << std::endl;
        CloseHandle(hFile);
        return nullptr;
    }

    LPVOID pMappedFile = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, fileSize);
    if (!pMappedFile) {
        std::cerr << "Failed to map view of file: " << GetLastError() << std::endl;
    }

    CloseHandle(hFileMapping);
    CloseHandle(hFile);
    return pMappedFile;
}

// 解析映射到内存中的.NET模块数据
void dumpMappedImg(LPVOID pMappedFile) {
    if (!pMappedFile) {
        std::cerr << "Invalid file mapping." << std::endl;
        return;
    }

    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)pMappedFile;
    PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((BYTE*)pMappedFile + pDosHeader->e_lfanew);
    PIMAGE_COR20_HEADER pCorHeader = (PIMAGE_COR20_HEADER)((BYTE*)pMappedFile + pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress);

    DWORD metaDataRVA = pCorHeader->MetaData.VirtualAddress;
    DWORD metaDataSize = pCorHeader->MetaData.Size;
    PVOID pMetaData = (PVOID)((BYTE*)pMappedFile + metaDataRVA);

    CComPtr<IMetaDataDispenserEx> pDispenser;
    HRESULT hr = CoCreateInstance(CLSID_CorMetaDataDispenser, nullptr, CLSCTX_INPROC_SERVER, IID_IMetaDataDispenserEx, (LPVOID*)&pDispenser);
    if (FAILED(hr)) {
        std::cerr << "Failed to create metadata dispenser: " << hr << std::endl;
        return;
    }

    CComPtr<IMetaDataImport> pImport;
    hr = pDispenser->OpenScopeOnMemory(pMetaData, metaDataSize, ofRead, IID_IMetaDataImport, (IUnknown**)&pImport);
    if (FAILED(hr)) {
        std::cerr << "Failed to open metadata scope: " << hr << std::endl;
        return;
    }

    // 提取元数据信息
    mdModule moduleToken;
    hr = pImport->GetModuleFromScope(&moduleToken);
    if (FAILED(hr)) {
        std::cerr << "Failed to get module token: " << hr << std::endl;
        return;
    }

    WCHAR moduleName[MAX_PATH];
    ULONG moduleNameLength;
    hr = pImport->GetModuleProps(moduleToken, moduleName, _countof(moduleName), &moduleNameLength, nullptr, nullptr);
    if (FAILED(hr)) {
        std::cerr << "Failed to get module properties: " << hr << std::endl;
        return;
    }
    std::wcout << L"Module name: " << moduleName << std::endl;

    // 提取.NET模块版本信息
    BYTE majorVersion = pCorHeader->MajorRuntimeVersion;
    BYTE minorVersion = pCorHeader->MinorRuntimeVersion;
    std::cout << "Version: " << static_cast<int>(majorVersion) << "." << static_cast<int>(minorVersion) << std::endl;

    // 提取数据表信息
    HCORENUM hEnum = nullptr;
    mdTableID tableIds[256];
    ULONG tableCount = 0;
    hr = pImport->EnumTables(&hEnum, tableIds, _countof(tableIds), &tableCount);
    if (FAILED(hr)) {
        std::cerr << "Failed to enumerate tables: " << hr << std::endl;
        return;
    }

    pImport->CloseEnum(hEnum);

    std::wcout << L"Tables:" << std::endl;
    for (ULONG i = 0; i < tableCount; i++) {
        WCHAR tableName[MAX_PATH];
        ULONG tableNameLength;
        hr = pImport->GetTableName(tableIds[i], tableName, _countof(tableName), &tableNameLength);
        if (FAILED(hr)) {
            std::cerr << "Failed to get table name: " << hr << std::endl;
            continue;
        }

        ULONG recordCount;
        hr = pImport->GetRowCount(tableIds[i], &recordCount);
        if (FAILED(hr)) {
            std::cerr << "Failed to get row count: " << hr << std::endl;
            continue;
        }

        std::wcout << L"  - " << tableName << L" (" << recordCount << L" records)" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_dotnet_module>" << std::endl;
        return 1;
    }
    CoInitialize(NULL);

    std::wstring filePath = CA2W(argv[1]);
    LPVOID pMappedFile = MapFileToMemory(filePath.c_str());
    if (pMappedFile) {
        dumpMappedImg(pMappedFile);
        UnmapViewOfFile(pMappedFile);
    }

    CoUninitialize();

    return 0;

}

