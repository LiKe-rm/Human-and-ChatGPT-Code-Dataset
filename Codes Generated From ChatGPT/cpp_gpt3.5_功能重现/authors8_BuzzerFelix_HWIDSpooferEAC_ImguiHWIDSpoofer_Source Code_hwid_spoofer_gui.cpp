#include <windows.h>
#include <d3d9.h>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx9.h>
#include <chrono>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
namespace gui {
    HWND CreateHWindow(HINSTANCE hInstance);
    void DestroyHWindow(HWND hWnd);
    IDirect3DDevice9* CreateDevice(HWND hWnd);
    void ResetDevice(IDirect3DDevice9* device);
    void DestroyDevice(IDirect3DDevice9* device);
    void CreateImGui(IDirect3DDevice9* device);
    void DestroyImGui();
    bool BeginRender();
    void EndRender(IDirect3DDevice9* device);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    HWND hWnd = gui::CreateHWindow(hInstance);
    IDirect3DDevice9* device = gui::CreateDevice(hWnd);
    gui::CreateImGui(device);

    while (gui::BeginRender()) {
        // Render ImGui window with "Spoof PC" button
        ImGui::Begin("Spoofer");
        if (ImGui::Button("Spoof PC")) {
            OpenSpoofer();
            break;
        }
        ImGui::End();

        DetectBadProcess();
        gui::EndRender(device);
    }

    gui::DestroyImGui();
    gui::DestroyDevice(device);
    gui::DestroyHWindow(hWnd);
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    // Handle window messages
    switch (uMsg) {
        case WM_SYSCOMMAND:
            if ((wParam & 0xFFF0) == SC_KEYMENU) // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MOUSEMOVE:
            ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
            return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// gui namespace
namespace gui {
    HWND CreateHWindow(HINSTANCE hInstance) {
        WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProc, 0L, 0L, hInstance, NULL, NULL, NULL, NULL, "ImGuiWindowClass", NULL };
        RegisterClassEx(&wc);
        HWND hWnd = CreateWindow("ImGuiWindowClass", "ImGui Example", WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, hInstance, NULL);
        ShowWindow(hWnd, SW_SHOWDEFAULT);
        UpdateWindow(hWnd);
        return hWnd;
    }

    void DestroyHWindow(HWND hWnd) {
        DestroyWindow(hWnd);
        UnregisterClass("ImGuiWindowClass", GetModuleHandle(NULL));
    }

    IDirect3DDevice9* CreateDevice(HWND hWnd) {
        LPDIRECT3D9 pD3D = Direct3DCreate9(D3D_SDK_VERSION);
        D3DPRESENT_PARAMETERS pp = {};
        pp.Windowed = TRUE;
        pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
        pp.BackBufferFormat = D3DFMT_UNKNOWN;
        pp.EnableAutoDepthStencil = TRUE;
        pp.AutoDepthStencilFormat = D3DFMT_D16;
        pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
        pp.hDeviceWindow = hWnd;

        IDirect3DDevice9* device;
        pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &pp, &device);
        pD3D->Release();
        return device;
    }

    void ResetDevice(IDirect3DDevice9* device) {
        ImGui_ImplDX9_InvalidateDeviceObjects();
        D3DPRESENT_PARAMETERS pp = {};
        device->GetPresentParameters(&pp);
        pp.BackBufferWidth = 0;
        pp.BackBufferHeight = 0;
        device->Reset(&pp);
        ImGui_ImplDX9_CreateDeviceObjects();
    }

    void DestroyDevice(IDirect3DDevice9* device) {
        device->Release();
    }

    void CreateImGui(IDirect3DDevice9* device) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui_ImplWin32_Init(hWnd);
        ImGui_ImplDX9_Init(device);
    }

    void DestroyImGui() {
        ImGui_ImplDX9_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }

    bool BeginRender() {
        // Handle Windows messages
        MSG msg;
        ZeroMemory(&msg, sizeof(msg));
        while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                return false;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Start new ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        return true;
    }

    void EndRender(IDirect3DDevice9* device) {
        // End ImGui frame
        ImGui::Render();
        device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
        if (device->BeginScene() >= 0) {
           
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            device->EndScene();
        }
        HRESULT result = device->Present(NULL, NULL, NULL, NULL);

        // Handle lost device
        if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            ResetDevice(device);
        }
    }
}

