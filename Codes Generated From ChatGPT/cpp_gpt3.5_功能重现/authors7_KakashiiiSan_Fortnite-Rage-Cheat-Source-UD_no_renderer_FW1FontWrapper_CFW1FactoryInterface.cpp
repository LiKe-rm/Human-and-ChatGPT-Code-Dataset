#include <d3d11.h>
#include <dwrite.h>
#include <FW1FontWrapper.h>

class CFW1Factory : public IFW1Factory {
public:
	CFW1Factory() : m_refCount(1) {}

	// IUnknown methods
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override {
		if (ppvObject == nullptr) {
			return E_INVALIDARG;
		}
		*ppvObject = nullptr;
		if (IsEqualIID(riid, __uuidof(IUnknown)) || IsEqualIID(riid, __uuidof(IFW1Factory))) {
			*ppvObject = static_cast<IFW1Factory*>(this);
		}
		else {
			return E_NOINTERFACE;
		}
		AddRef();
		return S_OK;
	}

	ULONG STDMETHODCALLTYPE AddRef() override {
		return InterlockedIncrement(&m_refCount);
	}

	ULONG STDMETHODCALLTYPE Release() override {
		ULONG newCount = InterlockedDecrement(&m_refCount);
		if (newCount == 0) {
			delete this;
		}
		return newCount;
	}

	// IFW1Factory methods
	HRESULT STDMETHODCALLTYPE CreateFontWrapper(
		ID3D11Device* pDevice,
		const WCHAR* pszFontFamily,
		IFW1FontWrapper** ppFontWrapper) override {
		if (pDevice == nullptr || pszFontFamily == nullptr || ppFontWrapper == nullptr) {
			return E_INVALIDARG;
		}

		*ppFontWrapper = nullptr;
		CFW1FontWrapper* pFontWrapper = new (std::nothrow) CFW1FontWrapper;
		if (pFontWrapper == nullptr) {
			return E_OUTOFMEMORY;
		}

		HRESULT hr = pFontWrapper->Init(pDevice, pszFontFamily);
		if (SUCCEEDED(hr)) {
			hr = pFontWrapper->QueryInterface(__uuidof(IFW1FontWrapper), reinterpret_cast<void**>(ppFontWrapper));
		}

		pFontWrapper->Release();
		return hr;
	}

	HRESULT STDMETHODCALLTYPE CreateGlyphVertexDrawer(
		IFW1GlyphVertexDrawer** ppGlyphVertexDrawer) override {
		if (ppGlyphVertexDrawer == nullptr) {
			return E_INVALIDARG;
		}

		*ppGlyphVertexDrawer = nullptr;
		CFW1GlyphVertexDrawer* pGlyphVertexDrawer = new (std::nothrow) CFW1GlyphVertexDrawer;
		if (pGlyphVertexDrawer == nullptr) {
			return E_OUTOFMEMORY;
		}

		HRESULT hr = pGlyphVertexDrawer->QueryInterface(__uuidof(IFW1GlyphVertexDrawer), reinterpret_cast<void**>(ppGlyphVertexDrawer));
		pGlyphVertexDrawer->Release();
		return hr;
	}

	HRESULT STDMETHODCALLTYPE CreateGlyphRenderStates(
		ID3D11Device* pDevice,
		IFW1GlyphRenderStates** ppGlyphRenderStates) override {
		if (pDevice == nullptr || ppGlyphRenderStates == nullptr) {
			return E_INVALIDARG;
		}

		*ppGlyphRenderStates = nullptr;
		CFW1GlyphRenderStates* pGlyphRenderStates = new (std::nothrow) CFW1GlyphRenderStates;
		if (pGlyphRenderStates == nullptr) {
			return E_OUTOFMEMORY;
		}

		HRESULT hr = pGlyphRenderStates->Init(pDevice);
		if (SUCCEEDED(hr)) {
			hr = pGlyphRenderStates->QueryInterface(__uuidof(IFW1GlyphRenderStates), reinterpret_cast<void**>(ppGlyphRenderStates));
		}

		pGlyphRenderStates->Release();
		return hr;
	}

	HRESULT STDMETHODCALLTYPE CreateTextRenderer(
		IDWriteFactory* pDWriteFactory,
		IFW1TextRenderer** ppTextRenderer) override {
		if (pDWriteFactory == nullptr || ppTextRenderer == nullptr) {
			return E_INVALIDARG;
		}

		*ppTextRenderer = nullptr;
		CFW1TextRenderer* pTextRenderer = new (std::nothrow) CFW1TextRenderer;
		if (pTextRenderer == nullptr) {
			return E_OUTOFMEMORY;
		}

		HRESULT hr = pTextRenderer->Init(pDWriteFactory);
		if (SUCCEEDED(hr)) {
			hr = pTextRenderer->QueryInterface(__uuidof(IFW1TextRenderer), reinterpret_cast<void**>(ppTextRenderer));
		}

		pTextRenderer->Release();
		return hr;
	}

	HRESULT STDMETHODCALLTYPE CreateTextGeometry(
		IFW1TextGeometry** ppTextGeometry) override {
		if (ppTextGeometry == nullptr) {
			return E_INVALIDARG;
		}

		*ppTextGeometry = nullptr;
		CFW1TextGeometry* pTextGeometry = new (std::nothrow) CFW1TextGeometry;
		if (pTextGeometry == nullptr) {
			return E_OUTOFMEMORY;
		}

		HRESULT hr = pTextGeometry->QueryInterface(__uuidof(IFW1TextGeometry), reinterpret_cast<void**>(ppTextGeometry));
		pTextGeometry->Release();
		return hr;
	}

	HRESULT STDMETHODCALLTYPE CreateGlyphProvider(
		ID3D11Device* pDevice,
		IDWriteFontFace* pFontFace,
		IFW1GlyphProvider** ppGlyphProvider) override {
		if (pDevice == nullptr || pFontFace == nullptr || ppGlyphProvider == nullptr) {
			return E_INVALIDARG;
		}

		*ppGlyphProvider = nullptr;
		CFW1GlyphProvider* pGlyphProvider = new (std::nothrow) CFW1GlyphProvider;
		if (pGlyphProvider == nullptr) {
			return E_OUTOFMEMORY;
		}

		HRESULT hr = pGlyphProvider->Init(pDevice, pFontFace);
		if (SUCCEEDED(hr)) {
			hr = pGlyphProvider->QueryInterface(__uuidof(IFW1GlyphProvider), reinterpret_cast<void**>(ppGlyphProvider));
		}

		pGlyphProvider->Release();
		return hr;
	}

	HRESULT STDMETHODCALLTYPE CreateDWriteRenderTarget(
		ID2D1RenderTarget* pRenderTarget,
		IFW1DWriteRenderTarget** ppDWriteRenderTarget) override {
		if (pRenderTarget == nullptr || ppDWriteRenderTarget == nullptr) {
			return E_INVALIDARG;
		}

		*ppDWriteRenderTarget = nullptr;
		CFW1DWriteRenderTarget* pDWriteRenderTarget = new (std::nothrow) CFW1DWriteRenderTarget;
		if (pDWriteRenderTarget == nullptr) {
			return E_OUTOFMEMORY;
		}

		HRESULT hr = pDWriteRenderTarget->Init(pRenderTarget);
		if (SUCCEEDED(hr)) {
			hr = pDWriteRenderTarget->QueryInterface(__uuidof(IFW1DWriteRenderTarget), reinterpret_cast<void**>(ppDWriteRenderTarget));
		}

		pDWriteRenderTarget->Release();
		return hr;
	}

	HRESULT STDMETHODCALLTYPE CreateGlyphAtlas(
		ID3D11Device* pDevice,
		UINT width,
		UINT height,
		DXGI_FORMAT format,
		IFW1GlyphAtlas** ppGlyphAtlas) override {
		if (pDevice == nullptr || ppGlyphAtlas == nullptr) {
			return E_INVALIDARG;
		}
		*ppGlyphAtlas = nullptr;
		CFW1GlyphAtlas* pGlyphAtlas = new (std::nothrow) CFW1GlyphAtlas;
		if (pGlyphAtlas == nullptr) {
			return E_OUTOFMEMORY;
		}

		HRESULT hr = pGlyphAtlas->Init(pDevice, width, height, format);
		if (SUCCEEDED(hr)) {
			hr = pGlyphAtlas->QueryInterface(__uuidof(IFW1GlyphAtlas), reinterpret_cast<void**>(ppGlyphAtlas));
		}

		pGlyphAtlas->Release();
		return hr;
	}

	HRESULT STDMETHODCALLTYPE CreateGlyphSheet(
		ID3D11Device* pDevice,
		UINT width,
		UINT height,
		DXGI_FORMAT format,
		IFW1GlyphSheet** ppGlyphSheet) override {
		if (pDevice == nullptr || ppGlyphSheet == nullptr) {
			return E_INVALIDARG;
		}
		*ppGlyphSheet = nullptr;
		CFW1GlyphSheet* pGlyphSheet = new (std::nothrow) CFW1GlyphSheet;
		if (pGlyphSheet == nullptr) {
			return E_OUTOFMEMORY;
		}

		HRESULT hr = pGlyphSheet->Init(pDevice, width, height, format);
		if (SUCCEEDED(hr)) {
			hr = pGlyphSheet->QueryInterface(__uuidof(IFW1GlyphSheet), reinterpret_cast<void**>(ppGlyphSheet));
		}

		pGlyphSheet->Release();
		return hr;
	}

	HRESULT STDMETHODCALLTYPE CreateColor(
		FLOAT red,
		FLOAT green,
		FLOAT blue,
		FLOAT alpha,
		IFW1ColorRGBA** ppColor) override {
		if (ppColor == nullptr) {
			return E_INVALIDARG;
		}

		*ppColor = nullptr;
		CFW1ColorRGBA* pColor = new (std::nothrow) CFW1ColorRGBA(red, green, blue, alpha);
		if (pColor == nullptr) {
			return E_OUTOFMEMORY;
		}

		HRESULT hr = pColor->QueryInterface(__uuidof(IFW1ColorRGBA), reinterpret_cast<void**>(ppColor));
		pColor->Release();
		return hr;
	}

private:
	ULONG m_refCount;
};

// Entry point for creating an instance of the factory
extern "C" HRESULT CreateFW1Factory(IFW1Factory * *ppFactory) {
	if (ppFactory == nullptr) {
		return E_INVALIDARG;
	}
	*ppFactory = nullptr;
	CFW1Factory* pFactory = new (std::nothrow) CFW1Factory;
	if (pFactory == nullptr) {
		return E_OUTOFMEMORY;
	}
	HRESULT hr = pFactory->QueryInterface(__uuidof(IFW1Factory), reinterpret_cast<void**>(ppFactory));
	pFactory->Release();
	return hr;
}
