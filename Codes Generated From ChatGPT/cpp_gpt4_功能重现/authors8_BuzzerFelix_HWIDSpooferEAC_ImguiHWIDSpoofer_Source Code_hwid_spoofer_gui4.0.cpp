#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "start_spoofer.h"
#include "nt_bsod.h"

// 使用的库
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// 定义窗口类名
const TCHAR* wndClassName = _T("ImGuiWindow");

// 函数声明
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int main()
{
    // 创建窗口
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = wndClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, _T("窗口注册失败"), _T("错误"), MB_ICONERROR);
        return 1;
    }

    HWND hWnd = CreateWindowEx(
        0,
        wndClassName,
        _T("ImGui Spoof PC"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        NULL, NULL,
        GetModuleHandle(NULL), NULL);

    if (!hWnd)
    {
        MessageBox(NULL, _T("窗口创建失败"), _T("错误"), MB_ICONERROR);
        return 1;
    }

    // 初始化DirectX 9
    IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (!pD3D)
    {
        MessageBox(NULL, _T("Direct3D 9 初始化失败"), _T("错误"), MB_ICONERROR);
        return 1;
    }

    D3DPRESENT_PARAMETERS pp = {};
    pp.Windowed = TRUE;
    pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    pp.hDeviceWindow = hWnd;
    pp.BackBufferFormat = D3DFMT_UNKNOWN;
    pp.EnableAutoDepthStencil = TRUE;
    pp.AutoDepthStencilFormat = D3DFMT_D16;

    IDirect3DDevice9* pDevice;
    if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &pp, &pDevice) < 0)
    {
        MessageBox(NULL, _T("创建Direct3D设备失败"), _T("错误"), MB_ICONERROR);
        pD3D->Release();
        return 1;
    }

    // 设置ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX9_Init(pDevice);

    // 主循环
    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        // 设置ImGui样式
        ImGui::StyleColorsDark();

        // 开始帧
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // ImGui窗口
        ImGui::Begin("Spoof PC");

        if (ImGui::Button("Spoof PC"))
        {
            start_spoofer();
        }

        ImGui::End();

        // 渲染
        pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(128, 128, 128, 255), 1.0f, 0);
        pDevice->BeginScene();

        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

        pDevice->EndScene();
        pDevice->Present(NULL, NULL, NULL, NULL);

        // 检测可疑进程
        DetectBadProcess();
    }

    // 清理资源
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    if (pDevice)
    {
        pDevice->Release();
    }
    if (pD3D)
    {
        pD3D->Release();
    }

    UnregisterClass(wndClassName, wc.hInstance);
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;
    switch (msg)
    {
        case WM_SIZE:
            if (wParam != SIZE_MINIMIZED)
                break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

