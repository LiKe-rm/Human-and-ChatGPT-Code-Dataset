#include <dwrite.h>
#include <FW1FontWrapper.h>
#include <vector>
#include <memory>

class CDirectWriteTextRenderer : public IDWriteTextRenderer,
	public IDWritePixelSnapping,
	public IFW1TextRenderer {
public:
	CDirectWriteTextRenderer(IFW1Factory* pFW1Factory)
		: m_refCount(1), m_pFW1Factory(pFW1Factory) {
		m_pFW1Factory->AddRef();
	}

	virtual ~CDirectWriteTextRenderer() {
		if (m_pFW1Factory) {
			m_pFW1Factory->Release();
		}
	}

	// IUnknown methods
	ULONG STDMETHODCALLTYPE AddRef() {
		return InterlockedIncrement(&m_refCount);
	}

	ULONG STDMETHODCALLTYPE Release() {
		ULONG newCount = InterlockedDecrement(&m_refCount);
		if (newCount == 0) {
			delete this;
		}
		return newCount;
	}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppvObject) {
		if (ppvObject == nullptr) {
			return E_POINTER;
		}

		if (iid == __uuidof(IUnknown) || iid == __uuidof(IDWritePixelSnapping)) {
			*ppvObject = static_cast<IDWritePixelSnapping*>(this);
		}
		else if (iid == __uuidof(IDWriteTextRenderer)) {
			*ppvObject = static_cast<IDWriteTextRenderer*>(this);
		}
		else if (iid == __uuidof(IFW1TextRenderer)) {
			*ppvObject = static_cast<IFW1TextRenderer*>(this);
		}
		else {
			*ppvObject = nullptr;
			return E_NOINTERFACE;
		}

		AddRef();
		return S_OK;
	}

	// IDWritePixelSnapping methods
	HRESULT STDMETHODCALLTYPE IsPixelSnappingDisabled(
		void* clientDrawingContext, BOOL* isDisabled) {
		if (isDisabled == nullptr) {
			return E_POINTER;
		}
		*isDisabled = FALSE;
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE GetCurrentTransform(
		void* clientDrawingContext, DWRITE_MATRIX* transform) {
		if (transform == nullptr) {
			return E_POINTER;
		}

		// Identity matrix for simplicity
		transform->m11 = 1.0f;
		transform->m12 = 0.0f;
		transform->m21 = 0.0f;
		transform->m22 = 1.0f;
		transform->dx = 0.0f;
		transform->dy = 0.0f;

		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE GetPixelsPerDip(
		void* clientDrawingContext, FLOAT* pixelsPerDip) {
		if (pixelsPerDip == nullptr) {
			return E_POINTER;
		}
		*pixelsPerDip = 1.0f;  // Assume 1:1 ratio for simplicity
		return S_OK;
	}

	// IDWriteTextRenderer methods
	HRESULT STDMETHODCALLTYPE DrawGlyphRun(
		void* clientDrawingContext,
		FLOAT baselineOriginX,
		FLOAT baselineOriginY,
		DWRITE_MEASURING_MODE measuringMode,
		DWRITE_GLYPH_RUN const* glyphRun,
		DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription,
		IUnknown* clientDrawingEffect) {
		HRESULT hr = S_OK;

		// Get the glyph provider

		IFW1GlyphProvider* pGlyphProvider;
		hr = m_pFW1Factory->GetGlyphProvider(&pGlyphProvider);
		if (FAILED(hr)) {
			return hr;
		}
		std::vector<FW1_VERTEXDATA> vertices;
		hr = pGlyphProvider->GetGlyphVertices(
			glyphRun->glyphCount, glyphRun->glyphIndices, glyphRun->glyphAdvances,
			glyphRun->glyphOffsets, glyphRun->isSideways,
			baselineOriginX, baselineOriginY,
			vertices.data(), vertices.size());
		if (FAILED(hr)) {
			pGlyphProvider->Release();
			return hr;
		}

		// Draw vertices using your rendering engine here
		// ...

		pGlyphProvider->Release();
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE DrawUnderline(
		void* clientDrawingContext,
		FLOAT baselineOriginX,
		FLOAT baselineOriginY,
		DWRITE_UNDERLINE const* underline,
		IUnknown* clientDrawingEffect) {
		// Not implemented
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE DrawStrikethrough(
		void* clientDrawingContext,
		FLOAT baselineOriginX,
		FLOAT baselineOriginY,
		DWRITE_STRIKETHROUGH const* strikethrough,
		IUnknown* clientDrawingEffect) {
		// Not implemented
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE DrawInlineObject(
		void* clientDrawingContext,
		FLOAT originX,
		FLOAT originY,
		IDWriteInlineObject* inlineObject,
		BOOL isSideways,
		BOOL isRightToLeft,
		IUnknown* clientDrawingEffect) {
		// Not implemented
		return E_NOTIMPL;
	}

	// IFW1TextRenderer methods
	HRESULT STDMETHODCALLTYPE DrawTextLayout(
		FLOAT originX,
		FLOAT originY,
		IDWriteTextLayout* pTextLayout,
		const FLOAT* pColorRGBA) {
		if (pTextLayout == nullptr) {
			return E_POINTER;
		}
		// Create a client drawing context
		std::unique_ptr<ClientDrawingContext> pClientDrawingContext(
			new ClientDrawingContext());
		if (pColorRGBA != nullptr) {
			pClientDrawingContext->color = D2D1::ColorF(
				pColorRGBA[0], pColorRGBA[1], pColorRGBA[2], pColorRGBA[3]);
		}
		else {
			pClientDrawingContext->color = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f);
		}

		// Draw the text layout
		HRESULT hr = pTextLayout->Draw(pClientDrawingContext.get(), this, originX, originY);

		return hr;
	}

private:
	ULONG m_refCount;
	IFW1Factory* m_pFW1Factory;

	struct ClientDrawingContext {
		D2D1_COLOR_F color;
	};
};