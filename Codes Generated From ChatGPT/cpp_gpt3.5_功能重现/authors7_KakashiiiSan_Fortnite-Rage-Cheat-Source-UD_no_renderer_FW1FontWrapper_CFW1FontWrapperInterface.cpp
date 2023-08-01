#include <d3d11.h>
#include <dwrite.h>
#include "FW1FontWrapper.h"

class CFW1FontWrapper : public IFW1FontWrapper {
public:
	CFW1FontWrapper() :
		m_cRefCount(1),
		m_pFactory(nullptr),
		m_pDevice(nullptr),
		m_pDWriteFactory(nullptr),
		m_pGlyphAtlas(nullptr),
		m_pGlyphProvider(nullptr),
		m_pRenderStates(nullptr),
		m_pVertexDrawer(nullptr) {
	}

	virtual ~CFW1FontWrapper() {
		if (m_pFactory) m_pFactory->Release();
		if (m_pDevice) m_pDevice->Release();
		if (m_pDWriteFactory) m_pDWriteFactory->Release();
		if (m_pGlyphAtlas) m_pGlyphAtlas->Release();
		if (m_pGlyphProvider) m_pGlyphProvider->Release();
		if (m_pRenderStates) m_pRenderStates->Release();
		if (m_pVertexDrawer) m_pVertexDrawer->Release();
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override {
		if (!ppvObject) return E_INVALIDARG;
		if (riid == __uuidof(IUnknown) || riid == __uuidof(IFW1FontWrapper)) {
			*ppvObject = static_cast<IFW1FontWrapper*>(this);
			AddRef();
			return S_OK;
		}
		*ppvObject = nullptr;
		return E_NOINTERFACE;
	}

	ULONG STDMETHODCALLTYPE AddRef() override {
		return ++m_cRefCount;
	}

	ULONG STDMETHODCALLTYPE Release() override {
		ULONG newCount = --m_cRefCount;
		if (newCount == 0) delete this;
		return newCount;
	}

	// IFW1FontWrapper
	HRESULT STDMETHODCALLTYPE GetFactory(IFW1Factory** ppFactory) override {
		if (!ppFactory) return E_INVALIDARG;
		*ppFactory = m_pFactory;
		if (m_pFactory) m_pFactory->AddRef();
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE GetDevice(ID3D11Device** ppDevice) override {
		if (!ppDevice) return E_INVALIDARG;
		*ppDevice = m_pDevice;
		if (m_pDevice) m_pDevice->AddRef();
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE GetDWriteFactory(IDWriteFactory** ppDWriteFactory) override {
		if (!ppDWriteFactory) return E_INVALIDARG;
		*ppDWriteFactory = m_pDWriteFactory;
		if (m_pDWriteFactory) m_pDWriteFactory->AddRef();
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE GetGlyphAtlas(IFW1GlyphAtlas** ppGlyphAtlas) override {
		if (!ppGlyphAtlas) return E_INVALIDARG;
		*ppGlyphAtlas = m_pGlyphAtlas;
		if (m_pGlyphAtlas) m_pGlyphAtlas->AddRef();
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE GetGlyphProvider(IFW1GlyphProvider** ppGlyphProvider) override {
		if (!ppGlyphProvider) return E_INVALIDARG;
		*ppGlyphProvider = m_pGlyphProvider;
		if (m_pGlyphProvider) m_pGlyphProvider->AddRef();
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE GetRenderStates(IFW1RenderStates** ppRenderStates) override {
		if (!ppRenderStates) return E_INVALIDARG;
		*ppRenderStates = m_pRenderStates;
		if (m_pRenderStates) m_pRenderStates->AddRef();
		return S_OK;
	}
	HRESULT STDMETHODCALLTYPE GetVertexDrawer(IFW1VertexDrawer** ppVertexDrawer) override {
		if (!ppVertexDrawer) return E_INVALIDARG;
		*ppVertexDrawer = m_pVertexDrawer;
		if (m_pVertexDrawer) m_pVertexDrawer->AddRef();
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE DrawTextLayout(
		ID3D11DeviceContext* pContext,
		IDWriteTextLayout* pTextLayout,
		FLOAT LayoutOriginX,
		FLOAT LayoutOriginY,
		UINT32 Color,
		UINT Flags
	) override {
		// Implement the DrawTextLayout functionality here.
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE DrawString(
		ID3D11DeviceContext* pContext,
		const WCHAR* pszString,
		const WCHAR* pszFontFamily,
		FLOAT FontSize,
		FLOAT X,
		FLOAT Y,
		UINT32 Color,
		UINT Flags
	) override {
		// Implement the DrawString functionality here.
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE MeasureString(
		const WCHAR* pszString,
		const WCHAR* pszFontFamily,
		FLOAT FontSize,
		FLOAT X,
		FLOAT Y,
		FLOAT* pWidth,
		FLOAT* pHeight
	) override {
		// Implement the MeasureString functionality here.
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE AnalyzeString(
		const WCHAR* pszString,
		const WCHAR* pszFontFamily,
		FLOAT FontSize,
		FLOAT X,
		FLOAT Y,
		UINT Flags,
		IFW1Geometry* pGeometry
	) override {
		// Implement the AnalyzeString functionality here.
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE AnalyzeTextLayout(
		IDWriteTextLayout* pTextLayout,
		FLOAT LayoutOriginX,
		FLOAT LayoutOriginY,
		UINT Flags,
		IFW1Geometry* pGeometry
	) override {
		// Implement the AnalyzeTextLayout functionality here.
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE DrawGeometry(
		ID3D11DeviceContext* pContext,
		IFW1Geometry* pGeometry,
		UINT32 Color,
		UINT Flags
	) override {
		// Implement the DrawGeometry functionality here.
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE Flush(ID3D11DeviceContext* pContext) override {
		// Implement the Flush functionality here.
		return E_NOTIMPL;
	}
private:
	ULONG m_cRefCount;
	IFW1Factory* m_pFactory;
	ID3D11Device* m_pDevice;
	IDWriteFactory* m_pDWriteFactory;
	IFW1GlyphAtlas* m_pGlyphAtlas;
	IFW1GlyphProvider* m_pGlyphProvider;
	IFW1RenderStates* m_pRenderStates;
	IFW1VertexDrawer* m_pVertexDrawer;
	// 禁止复制构造函数和赋值操作符
	CFW1FontWrapper(const CFW1FontWrapper&) = delete;
	CFW1FontWrapper& operator=(const CFW1FontWrapper&) = delete;

}
