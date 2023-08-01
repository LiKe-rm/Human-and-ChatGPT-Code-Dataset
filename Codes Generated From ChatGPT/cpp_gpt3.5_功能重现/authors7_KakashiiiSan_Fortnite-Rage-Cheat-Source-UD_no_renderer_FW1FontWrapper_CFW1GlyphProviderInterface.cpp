#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <dwrite.h>
#include <FW1FontWrapper.h>

namespace FW1FontWrapper {

	class CFW1GlyphProvider : public IFW1GlyphProvider {
	public:
		CFW1GlyphProvider(IDWriteFactory* pDWriteFactory, IDWriteFontCollection* pFontCollection);
		virtual ~CFW1GlyphProvider();

		// IUnknown methods
		HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject);
		ULONG STDMETHODCALLTYPE AddRef();
		ULONG STDMETHODCALLTYPE Release();

		// IFW1GlyphProvider methods
		HRESULT STDMETHODCALLTYPE GetGlyphAtlas(IFW1GlyphAtlas** ppGlyphAtlas);
		HRESULT STDMETHODCALLTYPE GetDWriteFactory(IDWriteFactory** ppDWriteFactory);
		HRESULT STDMETHODCALLTYPE GetDWriteFontCollection(IDWriteFontCollection** ppFontCollection);
		HRESULT STDMETHODCALLTYPE GetGlyphMapFromFont(
			IDWriteFontFace* pFontFace,
			FLOAT fontSize,
			UINT32 fontFlags,
			IFW1GlyphMap** ppGlyphMap
		);
		HRESULT STDMETHODCALLTYPE GetAtlasIdFromGlyphIndex(
			IFW1GlyphMap* pGlyphMap,
			UINT32 glyphIndex,
			IDWriteFontFace* pFontFace,
			UINT32 fontFlags,
			UINT32* pAtlasId
		);

	private:
		ULONG m_refCount;
		IDWriteFactory* m_pDWriteFactory;
		IDWriteFontCollection* m_pFontCollection;
		std::unique_ptr<IFW1GlyphAtlas> m_pGlyphAtlas;

		CFW1GlyphProvider(const CFW1GlyphProvider&) = delete;
		CFW1GlyphProvider& operator=(const CFW1GlyphProvider&) = delete;
	};

	CFW1GlyphProvider::CFW1GlyphProvider(IDWriteFactory* pDWriteFactory, IDWriteFontCollection* pFontCollection)
		: m_refCount(1),
		m_pDWriteFactory(pDWriteFactory),
		m_pFontCollection(pFontCollection),
		m_pGlyphAtlas(std::make_unique<FW1FontWrapper::CFW1GlyphAtlas>()) {
		m_pDWriteFactory->AddRef();
		m_pFontCollection->AddRef();
	}

	CFW1GlyphProvider::~CFW1GlyphProvider() {
		m_pDWriteFactory->Release();
		m_pFontCollection->Release();
	}

	HRESULT STDMETHODCALLTYPE CFW1GlyphProvider::QueryInterface(REFIID riid, void** ppvObject) {
		if (ppvObject == nullptr) {
			return E_POINTER;
		}
		if (riid == __uuidof(IUnknown) || riid == __uuidof(IFW1GlyphProvider)) {
			*ppvObject = static_cast<IFW1GlyphProvider*>(this);
			AddRef();
			return S_OK;
		}
		*ppvObject = nullptr;
		return E_NOINTERFACE;
	}

	ULONG STDMETHODCALLTYPE CFW1GlyphProvider::AddRef() {
		return ++m_refCount;
	}

	ULONG STDMETHODCALLTYPE CFW1GlyphProvider::Release() {
		ULONG newRefCount = --m_refCount;
		if (newRefCount == 0) {
			delete this;
		}
		return newRefCount;
	}

	HRESULT STDMETHODCALLTYPE CFW1GlyphProvider::GetGlyphAtlas(IFW1GlyphAtlas** ppGlyphAtlas) {
		if (ppGlyphAtlas == nullptr) {
			return E_POINTER;
		}
		*ppGlyphAtlas = m_pGlyphAtlas.get();
		(*ppGlyphAtlas)->AddRef();
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE CFW1GlyphProvider::GetDWriteFactory(IDWriteFactory** ppDWriteFactory) {
		if (ppDWriteFactory == nullptr) {
			return E_POINTER;
		}
		*ppDWriteFactory = m_pDWriteFactory;
		(*ppDWriteFactory)->AddRef();
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE CFW1GlyphProvider::GetDWriteFontCollection(IDWriteFontCollection** ppFontCollection) {
		if (ppFontCollection == nullptr) {
			return E_POINTER;
		}
		*ppFontCollection = m_pFontCollection;
		(*ppFontCollection)->AddRef();
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE CFW1GlyphProvider::GetGlyphMapFromFont(
		IDWriteFontFace* pFontFace,
		FLOAT fontSize,
		UINT32 fontFlags,
		IFW1GlyphMap** ppGlyphMap
	) {
		if (ppGlyphMap == nullptr) {
			return E_POINTER;
		}
		// Here, you should implement the logic to create a glyph map from the given font face,
		// font size, and font flags. For now, we will return E_NOTIMPL to indicate this method is not implemented.
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE CFW1GlyphProvider::GetAtlasIdFromGlyphIndex(
		IFW1GlyphMap* pGlyphMap,
		UINT32 glyphIndex,
		IDWriteFontFace* pFontFace,
		UINT32 fontFlags,
		UINT32* pAtlasId
	) {
		if (pAtlasId == nullptr) {
			return E_POINTER;
		}
		// Here, you should implement the logic to get the atlas ID from the given glyph map, glyph index,
		// font face, and font flags. For now, we will return E_NOTIMPL to indicate this method is not implemented.
		return E_NOTIMPL;
	}

} // namespace FW1FontWrapper
