#include <Windows.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <algorithm>

namespace Win32Helper {

// A class for managing window class registration.
    class WindowClassRegistrar {
        public:
            // Registers a window class if it has not been registered before.
            // Returns the class atom of the registered class.
        static ATOM RegisterWindowClass(const WNDCLASS& wndClass) {
            const std::wstring className(wndClass.lpszClassName);
            auto iter = classMap.find(className);
            if (iter == classMap.end()) {
                // Class not registered, register it now.
                wndClass.hInstance = GetModuleHandle(nullptr);
                const ATOM classAtom = RegisterClass(&wndClass);
                if (classAtom != 0) {
                    // Register succeeded, add the new class to the map.
                    classMap.emplace(className, classAtom);
                    return classAtom;
                } else {
                    // Register failed.
                    return 0;
                }
            } else {
                // Class already registered, return its atom.
                return iter->second;
            }
        }

        // Unregisters a window class if it is no longer used.
        static void UnregisterWindowClass(const WNDCLASS& wndClass) {
            const std::wstring className(wndClass.lpszClassName);
            auto iter = classMap.find(className);
            if (iter != classMap.end()) {
                // Class found in the map, decrement the reference count.
                const auto count = --classRefCount[iter->second];
                if (count == 0) {
                    // Reference count dropped to zero, unregister the class.
                    UnregisterClass(className.c_str(), GetModuleHandle(nullptr));
                    classMap.erase(iter);
                    classRefCount.erase(iter->second);
                }
            }
        }

        private:
            // Map from class names to class atoms.
        static std::unordered_map<std::wstring, ATOM> classMap;

        // Map from class atoms to reference counts.
        static std::unordered_map<ATOM, int> classRefCount;
    };

    std::unordered_map<std::wstring, ATOM> WindowClassRegistrar::classMap;
    std::unordered_map<ATOM, int> WindowClassRegistrar::classRefCount;

    // A helper function for converting a string to a LPCWSTR.
    inline LPCWSTR ToLPCWSTR(const std::string& str) {
        static std::vector<wchar_t> buffer;
        const auto requiredSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
        buffer.resize(requiredSize);
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer.data(), static_cast<int>(buffer.size()));
        return buffer.data();
    }

    // A class for managing Win32
    // windows.
    class Window {
        public:
        // Creates a new window with the given parameters.
        // The window will be initially hidden.
        Window(const std::string& title, int width, int height, WNDPROC wndProc) {
            const auto hInstance = GetModuleHandle(nullptr);
            WNDCLASS wc ={};
            wc.lpfnWndProc = wndProc;
            wc.hInstance = hInstance;
            wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
            wc.lpszClassName = ToLPCWSTR(title);
            const auto classAtom = WindowClassRegistrar::RegisterWindowClass(wc);
            if (classAtom == 0) {
                throw std::runtime_error("Failed to register window class");
            }
            classAtoms.push_back(classAtom);
            const DWORD style = WS_OVERLAPPEDWINDOW;
            RECT rect ={ 0, 0, width, height };
            AdjustWindowRect(&rect, style, FALSE);
            const auto hWnd = CreateWindow(MAKEINTATOM(classAtom), ToLPCWSTR(title), style,
                CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
                nullptr, nullptr, hInstance, nullptr);
            if (hWnd == nullptr) {
                throw std::runtime_error("Failed to create window");
            }
            this->hWnd = hWnd;
        }

        // Destroys the window.
        ~Window() {
            DestroyWindow(hWnd);
            for (const auto classAtom : classAtoms) {
                WNDCLASS wc ={};
                GetClassInfo(GetModuleHandle(nullptr), MAKEINTATOM(classAtom), &wc);
                WindowClassRegistrar::UnregisterWindowClass(wc);
            }
        }

        // Shows the window.
        void Show() const {
            ShowWindow(hWnd, SW_SHOWDEFAULT);
        }

        // Hides the window.
        void Hide() const {
            ShowWindow(hWnd, SW_HIDE);
        }

        // Returns the handle of the window.
        HWND GetHandle() const {
            return hWnd;
        }

        // Returns the device context of the window.
        HDC GetDC() const {
            return GetDC(hWnd);
        }

        // Releases the device context of the window.
        void ReleaseDC(HDC hdc) const {
            ::ReleaseDC(hWnd, hdc);
        }

        // Gets the current DPI of the window.
        int GetDpi() const {
            const auto hdc = GetDC(hWnd);
            const auto dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(hdc);
            return dpi;
        }

        // Scales a value from design DPI to actual DPI.
        int ScaleDpi(int value, int designDpi, int actualDpi) const {
            return MulDiv(value, actualDpi, designDpi);
        }
        private:
        // Handle of the window.
        HWND hWnd;
        // Class atoms used by the window.
        std::vector<ATOM> classAtoms;
    };

} // namespace Win32Helper
