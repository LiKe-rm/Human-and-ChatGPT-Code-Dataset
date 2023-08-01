#include <Windows.h>
#include <dia2.h>
#include <atlbase.h>
#include <string>
#include <unordered_map>

#define CHECK_SUCCESS(hr) if (FAILED(hr)) return hr;
#define E_PDB_DBG_NOT_FOUND HRESULT_FROM_WIN32(ERROR_NOT_FOUND)

class PDBHelper {
public:
    PDBHelper() {
        HRESULT hr = CoInitialize(NULL);
        CHECK_SUCCESS(hr);

        const char* path = getenv("_NT_SYMBOL_PATH");
        _sympath = path ? path : "%TEMP%";
    }

    ~PDBHelper() {
        if (_source) {
            _source.Release();
        }
        if (_session) {
            _session.Release();
        }
        CoUninitialize();
    }

    HRESULT Initialize(const char* exePath, DWORD64 baseAddress) {
        HRESULT hr = CreateDiaDataSource(&_source);
        CHECK_SUCCESS(hr);

        hr = _source->loadDataForExe(CComBSTR(exePath), CComBSTR(_sympath.c_str()), nullptr);
        CHECK_SUCCESS(hr);

        hr = _source->openSession(&_session);
        CHECK_SUCCESS(hr);

        CComPtr<IDiaSymbol> globalScope;
        hr = _session->get_globalScope(&globalScope);
        CHECK_SUCCESS(hr);

        hr = PopulateSymbols(globalScope);
        return hr;
    }

    HRESULT GetSymbolAddress(const std::string& symbolName, DWORD64* address) {
        auto it = _cache.find(symbolName);
        if (it != _cache.end()) {
            *address = it->second;
            return S_OK;
        }
        return E_PDB_DBG_NOT_FOUND;
    }

private:
    HRESULT CreateDiaDataSource(IDiaDataSource** source) {
        HRESULT hr = CoCreateInstance(CLSID_DiaSource, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(source));
        if (SUCCEEDED(hr)) {
            return hr;
        }

        HMODULE hMsDia = LoadLibrary("msdia140.dll");
        if (!hMsDia) {
            return HRESULT_FROM_WIN32(GetLastError());
        }

        typedef HRESULT(WINAPI* DLL_GET_CLASS_OBJECT)(REFCLSID, REFIID, LPVOID*);
        DLL_GET_CLASS_OBJECT fnDllGetClassObject = (DLL_GET_CLASS_OBJECT)GetProcAddress(hMsDia, "DllGetClassObject");
        if (!fnDllGetClassObject) {
            return HRESULT_FROM_WIN32(GetLastError());
        }

        CComPtr<IClassFactory> factory;
        hr = fnDllGetClassObject(CLSID_DiaSource, IID_PPV_ARGS(&factory));
        CHECK_SUCCESS(hr);

        hr = factory->CreateInstance(nullptr, IID_PPV_ARGS(source));
        return hr;
    }

    HRESULT PopulateSymbols(IDiaSymbol* globalScope) {
        CComPtr<IDiaEnumSymbols> enumSymbols;
        HRESULT hr = globalScope->findChildren(SymTagNull, nullptr, nsNone, &enumSymbols);
        CHECK_SUCCESS(hr);

        IDiaSymbol* symbol;
        ULONG celt;
        while (SUCCEEDED(enumSymbols->Next(1, &symbol,&celt)) && celt == 1) {
            CComBSTR name;
            DWORD64 addr;
            hr = symbol->get_name(&name);
            if (SUCCEEDED(hr)) {
                hr = symbol->get_virtualAddress(&addr);
                if (SUCCEEDED(hr)) {
                    std::string undecoratedName(name, name.Length());
                    // Optionally, you can use an external library to undecorate the symbol names
                    // undecorateSymbolName(undecoratedName);
                    _cache[undecoratedName] = addr;
                }
            }
            symbol->Release();
        }
        return S_OK;
    }

private:
    std::string _sympath;
    CComPtr<IDiaDataSource> _source;
    CComPtr<IDiaSession> _session;
    std::unordered_map<std::string, DWORD64> _cache;
};
