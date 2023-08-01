#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <dwrite.h>
#include <d2d1.h>

class CFw1GlyphProvider {
public:
	CFw1GlyphProvider();
	~CFw1GlyphProvider();

	HRESULT initGlyphProvider(IDWriteFactory* pDWriteFactory, ID2D1RenderTarget* pRenderTarget);
	UINT32 getFontIndexFromFontFace(IDWriteFontFace* pFontFace);
	std::wstring getUniqueNameFromFontFace(IDWriteFontFace* pFontFace);
	HRESULT insertNewGlyph(UINT32 fontIndex, UINT32 glyphIndex, DWRITE_GLYPH_METRICS* pGlyphMetrics);

private:
	struct GlyphData {
		DWRITE_GLYPH_METRICS metrics;
	};

	typedef std::map<UINT32, GlyphData> GlyphMap;
	typedef std::map<UINT32, GlyphMap> FontGlyphMap;

	IDWriteFactory* m_pDWriteFactory;
	ID2D1RenderTarget* m_pRenderTarget;
	FontGlyphMap m_fontGlyphMap;
};

CFw1GlyphProvider::CFw1GlyphProvider()
	: m_pDWriteFactory(nullptr)
	, m_pRenderTarget(nullptr) {
}

CFw1GlyphProvider::~CFw1GlyphProvider() {
	if (m_pRenderTarget) {
		m_pRenderTarget->Release();
		m_pRenderTarget = nullptr;
	}
	if (m_pDWriteFactory) {
		m_pDWriteFactory->Release();
		m_pDWriteFactory = nullptr;
	}
}

HRESULT CFw1GlyphProvider::initGlyphProvider(IDWriteFactory* pDWriteFactory, ID2D1RenderTarget* pRenderTarget) {
	if (!pDWriteFactory || !pRenderTarget) {
		return E_INVALIDARG;
	}
	pDWriteFactory->AddRef();
	m_pDWriteFactory = pDWriteFactory;
	pRenderTarget->AddRef();
	m_pRenderTarget = pRenderTarget;
	return S_OK;
}

UINT32 CFw1GlyphProvider::getFontIndexFromFontFace(IDWriteFontFace* pFontFace) {
	return pFontFace->GetIndex();
}

std::wstring CFw1GlyphProvider::getUniqueNameFromFontFace(IDWriteFontFace* pFontFace) {
	IDWriteLocalizedStrings* pFamilyNames;
	HRESULT hr = pFontFace->GetFamilyNames(&pFamilyNames);
	if (FAILED(hr)) {
		return L"";
	}

	UINT32 index = 0;
	BOOL exists = false;
	wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
	if (SUCCEEDED(GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH))) {
		hr = pFamilyNames->FindLocaleName(localeName, &index, &exists);
	}
	if (!exists) {
		hr = pFamilyNames->FindLocaleName(L"en-us", &index, &exists);
	}
	if (!exists) {
		index = 0;
	}

	UINT32 length = 0;
	hr = pFamilyNames->GetStringLength(index, &length);
	if (FAILED(hr)) {
		return L"";
	}

	std::wstring uniqueName;
	uniqueName.resize(length);
	hr = pFamilyNames->GetString(index, &uniqueName[0], length + 1);
	if (FAILED(hr)) {
		return L"";
	}

	DWRITE_FONT_SIMULATIONS simulations = pFontFace->GetSimulations();
	if (simulations & DWRITE_FONT_SIMULATIONS_BOLD) {
		uniqueName += L" Bold";
	}
	if (simulations & DWRITE_FONT_SIMULATIONS_OBLIQUE) {
		uniqueName += L" Oblique";
	}
	pFamilyNames->Release();
	return uniqueName;
}

HRESULT CFw1GlyphProvider::insertNewGlyph(UINT32 fontIndex, UINT32 glyphIndex, DWRITE_GLYPH_METRICS* pGlyphMetrics) {
	if (!pGlyphMetrics) {
		return E_INVALIDARG;
	}
	FontGlyphMap::iterator fontIter = m_fontGlyphMap.find(fontIndex);
	if (fontIter == m_fontGlyphMap.end()) {
		std::pair<FontGlyphMap::iterator, bool> result = m_fontGlyphMap.insert(std::make_pair(fontIndex, GlyphMap()));
		if (!result.second) {
			return E_FAIL;
		}
		fontIter = result.first;
	}

	GlyphMap& glyphMap = fontIter->second;
	if (glyphMap.find(glyphIndex) != glyphMap.end()) {
		return S_OK;
	}

	GlyphData glyphData;
	glyphData.metrics = *pGlyphMetrics;

	std::pair<GlyphMap::iterator, bool> result = glyphMap.insert(std::make_pair(glyphIndex, glyphData));
	if (!result.second) {
		return E_FAIL;
	}

	return S_OK;
}

int main() {
	HRESULT hr = S_OK;
	ID2D1Factory* pD2DFactory = nullptr;
	IDWriteFactory* pDWriteFactory = nullptr;
	ID2D1HwndRenderTarget* pRenderTarget = nullptr;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	if (SUCCEEDED(hr)) {
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));
	}
	if (SUCCEEDED(hr)) {
		RECT rc;
		GetClientRect(GetConsoleWindow(), &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

		hr = pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(GetConsoleWindow(), size),
			&pRenderTarget);
	}
	if (SUCCEEDED(hr)) {
		CFw1GlyphProvider glyphProvider;
		hr = glyphProvider.initGlyphProvider(pDWriteFactory, pRenderTarget);
		if (SUCCEEDED(hr)) {
			// Use glyphProvider for rendering and managing glyphs
		}
	}

	if (pRenderTarget) {
		pRenderTarget->Release();
	}
	if (pDWriteFactory) {
		pDWriteFactory->Release();
	}
	if (pD2DFactory) {
		pD2DFactory->Release();
	}

	return 0;
}
