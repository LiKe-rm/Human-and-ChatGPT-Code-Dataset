#include <d3d11.h>
#include "IFW1GlyphSheet.h"
#include "IFW1Factory.h"

class CFW1GlyphAtlas {
public:
	CFW1GlyphAtlas();
	~CFW1GlyphAtlas();

	HRESULT initGlyphAtlas(
		ID3D11Device* pDevice,
		UINT32 sheetWidth,
		UINT32 sheetHeight,
		bool hardwareCoordBuffer,
		bool allowOversizedGlyph,
		UINT32 maxGlyphCount,
		UINT32 mipLevelCount
	);

private:
	ID3D11Device* m_pDevice;
	UINT32 m_sheetWidth;
	UINT32 m_sheetHeight;
	bool m_hardwareCoordBuffer;
	bool m_allowOversizedGlyph;
	UINT32 m_maxGlyphCount;
	UINT32 m_mipLevelCount;
	IFW1GlyphSheet** m_glyphSheets;
	UINT32 m_sheetCount;
	UINT32 m_maxSheetCount;
	UINT32 m_currentSheetIndex;
	UINT32 m_flushedSheetIndex;

	HRESULT createGlyphSheet(IFW1Factory* pFactory, IFW1GlyphSheet** ppGlyphSheet);
};

CFW1GlyphAtlas::CFW1GlyphAtlas() :
	m_pDevice(nullptr),
	m_sheetWidth(0),
	m_sheetHeight(0),
	m_hardwareCoordBuffer(false),
	m_allowOversizedGlyph(false),
	m_maxGlyphCount(0),
	m_mipLevelCount(0),
	m_glyphSheets(nullptr),
	m_sheetCount(0),
	m_maxSheetCount(0),
	m_currentSheetIndex(0),
	m_flushedSheetIndex(0)
{}

CFW1GlyphAtlas::~CFW1GlyphAtlas() {
	if (m_glyphSheets) {
		for (UINT32 i = 0; i < m_sheetCount; ++i) {
			if (m_glyphSheets[i]) {
				m_glyphSheets[i]->Release();
			}
		}
		delete[] m_glyphSheets;
	}
	if (m_pDevice) {
		m_pDevice->Release();
	}
}

HRESULT CFW1GlyphAtlas::initGlyphAtlas(
	ID3D11Device* pDevice,
	UINT32 sheetWidth,
	UINT32 sheetHeight,
	bool hardwareCoordBuffer,
	bool allowOversizedGlyph,
	UINT32 maxGlyphCount,
	UINT32 mipLevelCount
) {
	if (!pDevice) {
		return E_INVALIDARG;
	}
	pDevice->AddRef();
	m_pDevice = pDevice;

	m_sheetWidth = sheetWidth;
	m_sheetHeight = sheetHeight;
	m_hardwareCoordBuffer = hardwareCoordBuffer;
	m_allowOversizedGlyph = allowOversizedGlyph;
	m_maxGlyphCount = maxGlyphCount;
	m_mipLevelCount = mipLevelCount;
	m_maxSheetCount = maxGlyphCount / (sheetWidth * sheetHeight / 64) + 1;

	m_glyphSheets = new IFW1GlyphSheet * [m_maxSheetCount];
	if (!m_glyphSheets) {
		return E_OUTOFMEMORY;
	}

	ZeroMemory(m_glyphSheets, m_maxSheetCount * sizeof(IFW1GlyphSheet*));

	return S_OK;
}

HRESULT CFW1GlyphAtlas::createGlyphSheet(IFW1Factory* pFactory, IFW1GlyphSheet** ppGlyphSheet) {
	if (!pFactory || !ppGlyphSheet) {
		return E_INVALIDARG;
	}
	HRESULT hr = pFactory->CreateGlyphSheet(
		m_pDevice,
		m_sheetWidth,
		m_sheetHeight,
		m_hardwareCoordBuffer,
		m_allowOversizedGlyph,
		m_mipLevelCount,
		ppGlyphSheet
	);

	if (SUCCEEDED(hr)) {
		m_glyphSheets[m_sheetCount++] = *ppGlyphSheet;
	}

	return hr;
}
