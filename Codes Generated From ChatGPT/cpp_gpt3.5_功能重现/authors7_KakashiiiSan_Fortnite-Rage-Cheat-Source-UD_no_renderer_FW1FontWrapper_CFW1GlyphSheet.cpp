#include <d3d11.h>
#include <dwrite.h>
#include <d2d1.h>
#include <vector>

#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d2d1.lib")

namespace FW1FontWrapper {

	class HeightRange {
	public:
		HeightRange() : left(0), right(0), height(0) {}
		HeightRange(UINT l, UINT r, UINT h) : left(l), right(r), height(h) {}

		UINT left;
		UINT right;
		UINT height;
	};

	class CFW1GlyphSheet {
	public:
		CFW1GlyphSheet();
		~CFW1GlyphSheet();

		HRESULT initGlyphSheet(IDWriteFontFace* pFontFace, UINT sheetWidth, UINT sheetHeight, const WCHAR* pCharacters, UINT numCharacters);
		HRESULT createDeviceResources(ID3D11Device* pDevice);

	private:
		UINT m_sheetWidth;
		UINT m_sheetHeight;
		ID3D11Texture2D* m_pGlyphSheetTexture;
		ID3D11ShaderResourceView* m_pGlyphSheetSRV;
		ID3D11Buffer* m_pGlyphCoordsBuffer;
		std::vector<HeightRange> m_heightRanges;

		void addHeightRange(UINT left, UINT right, UINT height);
		bool findPositionForGlyph(UINT glyphWidth, UINT glyphHeight, UINT& x, UINT& y);
	};

	// Constructor
	CFW1GlyphSheet::CFW1GlyphSheet() :
		m_sheetWidth(0),
		m_sheetHeight(0),
		m_pGlyphSheetTexture(nullptr),
		m_pGlyphSheetSRV(nullptr),
		m_pGlyphCoordsBuffer(nullptr) {
	}

	// Destructor
	CFW1GlyphSheet::~CFW1GlyphSheet() {
		if (m_pGlyphCoordsBuffer) m_pGlyphCoordsBuffer->Release();
		if (m_pGlyphSheetSRV) m_pGlyphSheetSRV->Release();
		if (m_pGlyphSheetTexture) m_pGlyphSheetTexture->Release();
	}

	HRESULT CFW1GlyphSheet::initGlyphSheet(IDWriteFontFace* pFontFace, UINT sheetWidth, UINT sheetHeight, const WCHAR* pCharacters, UINT numCharacters) {
		m_sheetWidth = sheetWidth;
		m_sheetHeight = sheetHeight;

		HRESULT hr = S_OK;

		// Initialize Direct2D factory
		ID2D1Factory* pD2DFactory = nullptr;
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
		if (FAILED(hr)) {
			return hr;
		}

		// Create a render target for glyph rendering
		D2D1_RENDER_TARGET_PROPERTIES rtProperties = D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_R8_UNORM, D2D1_ALPHA_MODE_IGNORE),
			0, 0
		);

		ID2D1RenderTarget* pRenderTarget = nullptr;
		hr = pD2DFactory->CreateWicBitmapRenderTarget(nullptr, rtProperties, &pRenderTarget);
		if (FAILED(hr)) {
			pD2DFactory->Release();
			return hr;
		}

		// Render glyphs using Direct2D and DirectWrite
		for (UINT i = 0; i < numCharacters; ++i) {
			// Get the glyph index for the character
			UINT16 glyphIndex = 0;
			pFontFace->GetGlyphIndices(&pCharacters[i], 1, &glyphIndex);

			// Get the glyph metrics
			DWRITE_GLYPH_METRICS glyphMetrics;
			pFontFace->GetDesignGlyphMetrics(&glyphIndex, 1, &glyphMetrics);

			// Calculate the glyph size in pixels
			float fontEmSize = static_cast<float>(glyphMetrics.designUnitsPerEm);
			float glyphWidth = ceilf(glyphMetrics.advanceWidth * m_sheetWidth / fontEmSize);
			float glyphHeight = ceilf(glyphMetrics.advanceHeight * m_sheetHeight / fontEmSize);

			// Find a position for the glyph in the glyph sheet
			UINT x, y;
			if (!findPositionForGlyph(static_cast<UINT>(glyphWidth), static_cast<UINT>(glyphHeight), x, y)) {
				hr = E_FAIL;
				break;
			}

			// Render the glyph to the render target
			pRenderTarget->BeginDraw();

			D2D1_RECT_F dstRect = D2D1::RectF(x, y, x + glyphWidth, y + glyphHeight);
			IDWriteGlyphRunAnalysis* pGlyphAnalysis = nullptr;
			DWRITE_GLYPH_RUN glyphRun = { 0 };
			glyphRun.fontFace = pFontFace;
			glyphRun.fontEmSize = fontEmSize;
			glyphRun.glyphCount = 1;
			glyphRun.glyphIndices = &glyphIndex;
			glyphRun.glyphAdvances = &glyphWidth;
			glyphRun.glyphOffsets = nullptr;
			glyphRun.isSideways = false;
			glyphRun.bidiLevel = 0;

			hr = pRenderTarget->CreateGlyphRunAnalysis(&glyphRun, 1.0f, nullptr, DWRITE_RENDERING_MODE_DEFAULT, DWRITE_MEASURING_MODE_NATURAL, 0, 0, &pGlyphAnalysis);
			if (SUCCEEDED(hr)) {
				ID2D1Brush* pBlackBrush = nullptr;
				pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBlackBrush);
				pRenderTarget->FillRectangle(dstRect, pBlackBrush);
				pBlackBrush->Release();
				pGlyphAnalysis->Release();
			}

			pRenderTarget->EndDraw();

			// Update the height range
			addHeightRange(x, y, static_cast<UINT>(glyphHeight));
		}

		// Clean up Direct2D resources
		pRenderTarget->Release();
		pD2DFactory->Release();

		return hr;
	}

	HRESULT CFW1GlyphSheet::createDeviceResources(ID3D11Device* pDevice) {
		HRESULT hr = S_OK;

		// Create the Direct3D resources (texture, shader resource view)
		D3D11_TEXTURE2D_DESC texDesc;
		ZeroMemory(&texDesc, sizeof(texDesc));
		texDesc.Width = m_sheetWidth;
		texDesc.Height = m_sheetHeight;
		texDesc.MipLevels = 1;
		texDesc.ArraySize = 1;
		texDesc.Format = DXGI_FORMAT_R8_UNORM;
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		texDesc.CPUAccessFlags = 0;
		texDesc.MiscFlags = 0;

		hr = pDevice->CreateTexture2D(&texDesc, nullptr, &m_pGlyphSheetTexture);
		if (FAILED(hr)) {
			return hr;
		}

		D3D11_SHADER_RESOURCE_VIEW
			_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format = texDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = 1;

		hr = pDevice->CreateShaderResourceView(m_pGlyphSheetTexture, &srvDesc, &m_pGlyphSheetSRV);
		if (FAILED(hr)) {
			m_pGlyphSheetTexture->Release();
			m_pGlyphSheetTexture = nullptr;
			return hr;
		}

		// Create optional coordinates buffer
		// TODO: Create the Direct3D buffer (m_pGlyphCoordsBuffer) to store the glyph coordinates, if necessary.

		return S_OK;
	}

	void CFW1GlyphSheet::addHeightRange(UINT left, UINT right, UINT height) {
		m_heightRanges.emplace_back(left, right, height);
	}

	bool CFW1GlyphSheet::findPositionForGlyph(UINT glyphWidth, UINT glyphHeight, UINT& x, UINT& y) {
		// Iterate through the height ranges to find a suitable position for the glyph
		for (const auto& range : m_heightRanges) {
			if (range.height >= glyphHeight && range.right - range.left >= glyphWidth) {
				x = range.left;
				y = range.height - glyphHeight;
				return true;
			}
		}

		// If no suitable position is found, check if there's enough space at the bottom of the glyph sheet
		if (m_heightRanges.empty() || m_heightRanges.back().height + glyphHeight <= m_sheetHeight) {
			x = 0;
			y = m_heightRanges.empty() ? 0 : m_heightRanges.back().height;
			return true;
		}

		// If no position is found, return false
		return false;
	}

} // namespace FW1FontWrapper
