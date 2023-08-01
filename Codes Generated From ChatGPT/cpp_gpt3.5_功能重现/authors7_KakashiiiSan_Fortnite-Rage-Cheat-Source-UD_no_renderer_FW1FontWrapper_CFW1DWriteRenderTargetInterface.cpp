#include <d3d11.h>
#include <dwrite.h>
#include <FW1FontWrapper.h>

class CFW1DWriteRenderTarget : public IFW1DWriteRenderTarget {
public:
	// Constructor and destructor
	CFW1DWriteRenderTarget();
	virtual ~CFW1DWriteRenderTarget();

	// IUnknown interface
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject);
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();

	// IFW1DWriteRenderTarget interface
	HRESULT STDMETHODCALLTYPE DrawGlyphTemp(
		IDWriteFontFace* pFontFace,
		UINT16 GlyphIndex,
		FLOAT FontSize,
		DWRITE_RENDERING_MODE RenderingMode,
		DWRITE_MEASURING_MODE MeasuringMode,
		FW1_GLYPHIMAGEDATA* pOutData
	);

private:
	LONG m_cRef;
};

// Constructor
CFW1DWriteRenderTarget::CFW1DWriteRenderTarget() :
	m_cRef(1) {
}

// Destructor
CFW1DWriteRenderTarget::~CFW1DWriteRenderTarget() {
}

HRESULT STDMETHODCALLTYPE CFW1DWriteRenderTarget::QueryInterface(REFIID riid, void** ppvObject) {
	if (ppvObject == nullptr) {
		return E_POINTER;
	}

	if (riid == __uuidof(IUnknown) || riid == __uuidof(IFW1DWriteRenderTarget)) {
		*ppvObject = static_cast<IFW1DWriteRenderTarget*>(this);
		AddRef();
		return S_OK;
	}

	*ppvObject = nullptr;
	return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE CFW1DWriteRenderTarget::AddRef() {
	return InterlockedIncrement(&m_cRef);
}

ULONG STDMETHODCALLTYPE CFW1DWriteRenderTarget::Release() {
	ULONG newCount = InterlockedDecrement(&m_cRef);
	if (newCount == 0) {
		delete this;
	}
	return newCount;
}

HRESULT STDMETHODCALLTYPE CFW1DWriteRenderTarget::DrawGlyphTemp(
	IDWriteFontFace* pFontFace,
	UINT16 GlyphIndex,
	FLOAT FontSize,
	DWRITE_RENDERING_MODE RenderingMode,
	DWRITE_MEASURING_MODE MeasuringMode,
	FW1_GLYPHIMAGEDATA* pOutData
) {
	if (!pFontFace || !pOutData) {
		return E_INVALIDARG;
	}

	// Get the glyph metrics
	DWRITE_GLYPH_METRICS glyphMetrics;
	HRESULT hr = pFontFace->GetGdiCompatibleGlyphMetrics(FontSize, 1.0f, nullptr, FALSE, &GlyphIndex, 1, &glyphMetrics);
	if (FAILED(hr)) {
		return hr;
	}

	// Calculate pixel metrics
	FLOAT dpiScale = 96.0f;
	FLOAT advanceWidth = glyphMetrics.advanceWidth * FontSize / pFontFace->GetUnitsPerEm();
	FLOAT leftSideBearing = glyphMetrics.leftSideBearing * FontSize / pFontFace->GetUnitsPerEm();
	FLOAT rightSideBearing = glyphMetrics.rightSideBearing * FontSize / pFontFace->GetUnitsPerEm();
	FLOAT topSideBearing = glyphMetrics.topSideBearing * FontSize / pFontFace->GetUnitsPerEm();
	FLOAT bottomSideBearing = glyphMetrics.bottomSideBearing * FontSize / pFontFace->GetUnitsPerEm();
	FLOAT verticalOriginY = glyphMetrics.verticalOriginY * FontSize / pFontFace->GetUnitsPerEm();

	// Set drawing information
	DWRITE_GLYPH_RUN glyphRun;
	glyphRun.fontFace = pFontFace;
	glyphRun.fontSize = FontSize;
	glyphRun.glyphCount = 1;
	glyphRun.glyphIndices = &GlyphIndex;
	glyphRun.glyphAdvances = &advanceWidth;
	glyphRun.glyphOffsets = nullptr;
	glyphRun.isSideways = FALSE;
	glyphRun.bidiLevel = 0;
	// Clear background
	memset(pOutData->pGlyphData, 0, pOutData->GlyphDataPitch * pOutData->GlyphHeight);

	// Set rendering parameters
	DWRITE_MATRIX transformMatrix = { 1.0f, 0.0f, 0.0f, 1.0f, -leftSideBearing, -verticalOriginY };
	DWRITE_RENDERING_PARAMS renderingParams = {};
	renderingParams.gamma = 2.2f;
	renderingParams.enhancedContrast = 1.0f;
	renderingParams.clearTypeLevel = 1.0f;
	renderingParams.pixelGeometry = DWRITE_PIXEL_GEOMETRY_FLAT;
	renderingParams.renderingMode = RenderingMode;

	// Draw the glyph using DrawGlyphRun method
	hr = this->DrawGlyphRun(
		0, 0,
		MeasuringMode,
		&glyphRun,
		&transformMatrix,
		0xFFFFFFFF,
		nullptr,
		nullptr,
		&renderingParams,
		nullptr,
		nullptr,
		0
	);
	if (FAILED(hr)) {
		return hr;
	}

	// Clip the glyph to avoid buffer overflow
	UINT32 clippedWidth = min(pOutData->GlyphWidth, static_cast<UINT32>(advanceWidth));
	UINT32 clippedHeight = min(pOutData->GlyphHeight, static_cast<UINT32>(glyphMetrics.advanceHeight));
	pOutData->GlyphWidth = clippedWidth;
	pOutData->GlyphHeight = clippedHeight;

	// Return the rendered glyph data
	return S_OK;
}
