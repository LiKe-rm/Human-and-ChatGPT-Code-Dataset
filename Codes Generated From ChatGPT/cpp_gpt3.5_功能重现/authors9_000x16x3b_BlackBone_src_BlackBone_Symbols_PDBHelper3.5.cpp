#include <windows.h>
#include <atlbase.h>
#include <atlcom.h>
#include <dia2.h>
#include <vector>
#include <string>
#include <algorithm>

class PDBHelper {
public:
    PDBHelper() {
        CoInitialize(nullptr);
        const char* env_sympath = getenv("_NT_SYMBOL_PATH");
        if (env_sympath != nullptr) {
            _sympath = env_sympath;
        }
        else {
            char temp_path[MAX_PATH] = { 0 };
            GetTempPathA(MAX_PATH, temp_path);
            _sympath = temp_path;
        }
    }

    ~PDBHelper() {
        if (_pGlobalScope != nullptr) {
            _pGlobalScope->Release();
        }
        if (_pSession != nullptr) {
            _pSession->Release();
        }
        if (_pSource != nullptr) {
            _pSource->Release();
        }
        CoUninitialize();
    }

    HRESULT Init(const char* pe_file_path, DWORD64 base_address) {
        HRESULT hr = CreateDiaDataSource(& _pSource);
        CHECK_SUCCESS(hr);

        hr = _pSource->loadDataForExe(CComBSTR(pe_file_path), CComBSTR(_sympath.c_str()), nullptr);
        CHECK_SUCCESS(hr);

        hr = _pSource->openSession(&_pSession);
        CHECK_SUCCESS(hr);

        hr = _pSession->get_globalScope(&_pGlobalScope);
        CHECK_SUCCESS(hr);

        hr = PopulateSymbols(base_address);
        CHECK_SUCCESS(hr);

        return hr;
    }

    HRESULT GetSymbolAddress(const char* symbol_name, DWORD64& address) {
        auto it = std::find_if(_cache.begin(), _cache.end(), [symbol_name](const std::pair<std::string, DWORD64>& pair) {
            return pair.first.find(symbol_name) != std::string::npos;
        });

        if (it != _cache.end()) {
            address = it->second;
            return S_OK;
        }

        return E_PDB_DBG_NOT_FOUND;
    }

private:
    std::string _sympath;
    IDiaDataSource* _pSource = nullptr;
    IDiaSession* _pSession = nullptr;
    IDiaSymbol* _pGlobalScope = nullptr;
    std::vector<std::pair<std::string, DWORD64>> _cache;

#define CHECK_SUCCESS(hr) if (FAILED(hr)) { return hr; }

    HRESULT CreateDiaDataSource(IDiaDataSource** ppSource) {
        HRESULT hr = CoCreateInstance(CLSID_DiaSource, nullptr, CLSCTX_INPROC_SERVER, __uuidof(IDiaDataSource), (void**)ppSource);
        if (FAILED(hr)) {
            HMODULE hMod = LoadLibraryA("msdia140.dll");
            if (hMod != nullptr) {
                typedef HRESULT(WINAPI* DllGetClassObjectFunc)(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
                DllGetClassObjectFunc pfnDllGetClassObject = (DllGetClassObjectFunc)GetProcAddress(hMod, "DllGetClassObject");
                if (pfnDllGetClassObject != nullptr) {
                    IClassFactory* pClassFactory = nullptr;
                    hr = pfnDllGetClassObject(CLSID_DiaSource, IID_IClassFactory, (void**)& pClassFactory);
                    if (SUCCEEDED(hr)) {
                        hr = pClassFactory->CreateInstance(nullptr, __uuidof(IDiaDataSource), (void**)ppSource);
                        pClassFactory->Release();
                    }
                }
                FreeLibrary(hMod);
            }
        }
        return hr;
    }

    HRESULT PopulateSymbols(DWORD64 base_address) {
        HRESULT hr = S_OK;
        IDiaEnumSymbols* pEnumSymbols = nullptr;
        hr = _pGlobalScope->findChildren(SymTagNull, nullptr, nsNone, &pEnumSymbols);
        CHECK_SUCCESS(hr);

        IDiaSymbol* pSymbol = nullptr;
        ULONG celt = 0;
        while (SUCCEEDED(pEnumSymbols->Next(1, &pSymbol, &celt)) && celt == 1) {
            BSTR name = nullptr;
            DWORD64 address = 0;
            hr = pSymbol->get_name(&name);
            if (FAILED(hr) || name == nullptr) {
                pSymbol->Release();
                continue;
            }

            hr = pSymbol->get_virtualAddress(&address);
            if (FAILED(hr)) {
                CoTaskMemFree(name);
                pSymbol->Release();
                continue;
            }

            if (address > 0) {
                address += base_address;
                std::string str_name = CW2A(name);
                size_t pos = str_name.find('@');
                if (pos != std::string::npos) {
                    str_name = str_name.substr(0, pos);
                }
                _cache.push_back(std::make_pair(str_name, address));
            }

            CoTaskMemFree(name);
            pSymbol->Release();
        }

        pEnumSymbols->Release();
        return hr;
    }
};