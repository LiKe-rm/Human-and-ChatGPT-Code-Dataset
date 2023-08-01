#include <d2d1.h>
#include <dwrite.h>
#include <wrl/client.h>

class Direct2DRenderer {
public:
    Direct2DRenderer();
    ~Direct2DRenderer();

    HRESULT Initialize();
    HRESULT PrintFPS(float fps);
    void Shutdown();

private:
    template<typename T>
    struct Expected {
        T Value;
        bool Error;

        Expected(T value, bool error) : Value(value), Error(error) {}
    };

    Expected<ID2D1Factory*> CreateD2DFactory();
    Expected<IDWriteFactory*> CreateDWriteFactory();
    Expected<ID2D1RenderTarget*> CreateRenderTarget();
    Expected<IDWriteTextFormat*> CreateTextFormat();

    Microsoft::WRL::ComPtr<ID2D1Factory> m_d2dFactory;
    Microsoft::WRL::ComPtr<IDWriteFactory> m_dWriteFactory;
    Microsoft::WRL::ComPtr<ID2D1RenderTarget> m_renderTarget;
    Microsoft::WRL::ComPtr<IDWriteTextFormat> m_textFormat;
};

Direct2DRenderer::Direct2DRenderer() {
    HRESULT hr = Initialize();
    if (FAILED(hr)) {
        Shutdown();
    }
}

Direct2DRenderer::~Direct2DRenderer() {
    Shutdown();
}

HRESULT Direct2DRenderer::Initialize() {
    auto d2dFactory = CreateD2DFactory();
    if (d2dFactory.Error) {
        return E_FAIL;
    }
    m_d2dFactory = d2dFactory.Value;

    auto dWriteFactory = CreateDWriteFactory();
    if (dWriteFactory.Error) {
        return E_FAIL;
    }
    m_dWriteFactory = dWriteFactory.Value;

    auto renderTarget = CreateRenderTarget();
    if (renderTarget.Error) {
        return E_FAIL;
    }
    m_renderTarget = renderTarget.Value;

    auto textFormat = CreateTextFormat();
    if (textFormat.Error) {
        return E_FAIL;
    }
    m_textFormat = textFormat.Value;

    return S_OK;
}

HRESULT Direct2DRenderer::PrintFPS(float fps) {
    m_renderTarget->BeginDraw();

    WCHAR buffer[64];
    swprintf_s(buffer, L"FPS: %.2f", fps);

    D2D1_RECT_F layoutRect = D2D1::RectF(0, 0, 200, 50);
    m_renderTarget->DrawTextW(buffer, wcslen(buffer), m_textFormat.Get(), &layoutRect, m_renderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f)));

    HRESULT hr = m_renderTarget->EndDraw();
    if (hr == D2DERR_RECREATE_TARGET) {
        hr = S_OK;
        m_renderTarget.ReleaseAndGetAddressOf();
        auto renderTarget = CreateRenderTarget();
        if (renderTarget.Error) {
            return E_FAIL;
        }
        m_renderTarget = renderTarget.Value;
    }

    return hr;
}

void Direct2DRenderer::Shutdown() {
    m_textFormat.Reset();
    m_renderTarget.Reset();
    m_dWriteFactory.Reset();
    m_d2dFactory.Reset();
}

Direct2DRenderer::Expected<ID2D1Factory*> Direct2DRenderer::CreateD2DFactory() {
    ID2D1Factory* factory;
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
    if (FAILED(hr)) {
        return Expected<ID2D1Factory*>(nullptr, true);
    }
    return Expected<ID2D1Factory*>(factory, false);
}

Direct2DRenderer::Expected<IDWriteFactory*> Direct2DRenderer::CreateDWriteFactory() {
    IDWriteFactory* factory;
    HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&factory));
    if (FAILED(hr)) {
        return Expected<IDWriteFactory*>(nullptr, true);
    }
    return Expected<IDWriteFactory*>(factory, false);
}

Direct2DRenderer::Expected<ID2D1RenderTarget*> Direct2DRenderer::CreateRenderTarget() {
    ID2D1HwndRenderTarget* renderTarget;
    D2D1_RENDER_TARGET_PROPERTIES rtProps = D2D1::RenderTargetProperties();
    D2D1_HWND_RENDER_TARGET_PROPERTIES hwndProps = D2D1::HwndRenderTargetProperties(GetActiveWindow(), D2D1::SizeU(800, 600));
    HRESULT hr = m_d2dFactory->CreateHwndRenderTarget(&rtProps, &hwndProps, &renderTarget);
    if (FAILED(hr)) {
        return Expected<ID2D1RenderTarget*>(nullptr, true);
    }
    return Expected<ID2D1RenderTarget*>(renderTarget, false);
}

Direct2DRenderer::Expected<IDWriteTextFormat*> Direct2DRenderer::CreateTextFormat() {
    IDWriteTextFormat* textFormat;
    HRESULT hr = m_dWriteFactory->CreateTextFormat(L"Arial", nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 18.0f, L"en-us", &textFormat);
    if (FAILED(hr)) {
        return Expected<IDWriteTextFormat*>(nullptr, true);
    }
    return Expected<IDWriteTextFormat*>(textFormat, false);
}
