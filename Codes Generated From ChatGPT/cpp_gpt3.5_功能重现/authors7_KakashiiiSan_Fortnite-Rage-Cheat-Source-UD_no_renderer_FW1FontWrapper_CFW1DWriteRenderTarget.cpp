#include <Windows.h>
#include <dwrite_1.h>
#include <d2d1_1.h>
#include <stdexcept>

#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d2d1.lib")

class CFW1DWriteRenderTarget {
public:
	CFW1DWriteRenderTarget();
	~CFW1DWriteRenderTarget();

	HRESULT initRenderTarget(UINT width, UINT height);
	HRESULT createRenderTarget();
	HRESULT initGlyphData(IDWriteFontFace* fontFace, const WCHAR* glyphIndices, UINT glyphCount, DWRITE_GLYPH_RUN* glyphRun);

private:
	UINT m_width;
	UINT m_height;
	IDWriteFactory1* m_pDWriteFactory;
	ID2D1Factory1* m_pD2DFactory;
	ID2D1RenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pSolidColorBrush;
};

CFW1DWriteRenderTarget::CFW1DWriteRenderTarget()
	: m_width(0),
	m_height(0),
	m_pDWriteFactory(nullptr),
	m_pD2DFactory(nullptr),
	m_pRenderTarget(nullptr),
	m_pSolidColorBrush(nullptr) {
	HRESULT hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory1),
		reinterpret_cast<IUnknown**>(&m_pDWriteFactory));

	if (FAILED(hr)) {
		throw std::runtime_error("Failed to create DirectWrite factory.");
	}

	hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		__uuidof(ID2D1Factory1),
		nullptr,
		reinterpret_cast<IUnknown**>(&m_pD2DFactory));

	if (FAILED(hr)) {
		throw std::runtime_error("Failed to create Direct2D factory.");
	}
}

CFW1DWriteRenderTarget::~CFW1DWriteRenderTarget() {
	if (m_pSolidColorBrush) {
		m_pSolidColorBrush->Release();
	}
	if (m_pRenderTarget) {
		m_pRenderTarget->Release();
	}
	if (m_pD2DFactory) {
		m_pD2DFactory->Release();
	}
	if (m_pDWriteFactory) {
		m_pDWriteFactory->Release();
	}
}

HRESULT CFW1DWriteRenderTarget::initRenderTarget(UINT width, UINT height) {
	m_width = width;
	m_height = height;

	return createRenderTarget();
}

HRESULT CFW1DWriteRenderTarget::createRenderTarget() {
	HRESULT hr = S_OK;

	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE));

	hr = m_pD2DFactory->CreateWicBitmapRenderTarget(
		nullptr,
		D2D1::RenderTargetProperties(),
		&m_pRenderTarget);

	if (FAILED(hr)) {
		return hr;
	}

	hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pSolidColorBrush);

	return hr;
}

HRESULT CFW1DWriteRenderTarget::initGlyphData(IDWriteFontFace* fontFace, const WCHAR* glyphIndices, UINT glyphCount, DWRITE_GLYPH_RUN* glyphRun) {
	if (!fontFace || !glyphIndices || !glyphRun) {
		return E_INVALIDARG;
	}

	HRESULT hr = S_OK;

	glyphRun->fontFace = fontFace;
	glyphRun->fontEmSize = 12.0f;
	glyphRun->glyphCount = glyphCount;
	glyphRun->glyphIndices = glyphIndices;
	glyphRun->glyphAdvances = nullptr;
	glyphRun->glyphOffsets = nullptr;
	glyphRun->isSideways = false;
	glyphRun->bidiLevel = 0;
	FLOAT* advances = new FLOAT[glyphCount];
	DWRITE_GLYPH_OFFSET* offsets = new DWRITE_GLYPH_OFFSET[glyphCount];

	if (!advances || !offsets) {
		hr = E_OUTOFMEMORY;
		goto cleanup;
	}

	hr = fontFace->GetDesignGlyphAdvances(glyphCount, glyphIndices, advances, false);

	if (FAILED(hr)) {
		goto cleanup;
	}

	hr = fontFace->GetDesignGlyphMetrics(glyphCount, glyphIndices, nullptr, false);

	if (FAILED(hr)) {
		goto cleanup;
	}

	for (UINT i = 0; i < glyphCount; ++i) {
		advances[i] /= fontFace->GetDesignUnitsPerEm();
		offsets[i].advanceOffset = 0;
		offsets[i].ascenderOffset = 0;
	}

	glyphRun->glyphAdvances = advances;
	glyphRun->glyphOffsets = offsets;
cleanup:
	if (FAILED(hr)) {
		if (advances) {
			delete[] advances;
		}
		if (offsets) {
			delete[] offsets;
		}
	}
	return hr;
}
