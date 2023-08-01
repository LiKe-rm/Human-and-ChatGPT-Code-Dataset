#include "CFW1GlyphAtlasInterface.h"
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>
#include <cstring>

class CFW1GlyphAtlas : public CFW1GlyphAtlasInterface {
public:
	CFW1GlyphAtlas(ID3D11Device* pDevice) :
		m_refCount(1),
		m_pDevice(pDevice) {
		m_pDevice->AddRef();
	}

	virtual ~CFW1GlyphAtlas() {
		for (auto& texture : m_textureArray) {
			texture->Release();
		}
		m_pDevice->Release();
	}

	ULONG STDMETHODCALLTYPE AddRef() override {
		return ++m_refCount;
	}

	ULONG STDMETHODCALLTYPE Release() override {
		ULONG newRefCount = --m_refCount;
		if (newRefCount == 0) {
			delete this;
		}
		return newRefCount;
	}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override {
		if (!ppvObject) {
			return E_INVALIDARG;
		}
		if (riid == __uuidof(IUnknown) || riid == __uuidof(CFW1GlyphAtlasInterface)) {
			*ppvObject = static_cast<CFW1GlyphAtlasInterface*>(this);
		}
		else {
			*ppvObject = nullptr;
			return E_NOINTERFACE;
		}
		AddRef();
		return S_OK;
	}

	ID3D11Device* STDMETHODCALLTYPE GetDevice() override {
		m_pDevice->AddRef();
		return m_pDevice;
	}

	UINT STDMETHODCALLTYPE GetTotalGlyphCount() override {
		return static_cast<UINT>(m_glyphDataMap.size());
	}

	UINT STDMETHODCALLTYPE GetAtlasCount() override {
		return static_cast<UINT>(m_textureArray.size());
	}

	ID3D11ShaderResourceView* STDMETHODCALLTYPE GetAtlas(UINT index) override {
		if (index >= m_textureArray.size()) {
			return nullptr;
		}
		m_textureArray[index]->AddRef();
		return m_textureArray[index];
	}

	bool STDMETHODCALLTYPE GetTextureCoordinates(UINT glyphIndex, UINT atlasIndex, float* pU, float* pV, float* pSizeU, float* pSizeV) override {
		auto it = m_glyphDataMap.find(glyphIndex);
		if (it == m_glyphDataMap.end() || atlasIndex >= m_textureArray.size()) {
			return false;
		}
		GlyphData& glyphData = it->second;
		*pU = glyphData.u;
		*pV = glyphData.v;
		*pSizeU = glyphData.sizeU;
		*pSizeV = glyphData.sizeV;
		return true;
	}

	HRESULT STDMETHODCALLTYPE BindAtlas(UINT atlasIndex) override {
		if (atlasIndex >= m_textureArray.size()) {
			return E_INVALIDARG;
		}
		ID3D11ShaderResourceView* pTextureArray[] = { m_textureArray[atlasIndex] };
		ID3D11DeviceContext* pContext;
		m_pDevice->GetImmediateContext(&pContext);
		pContext->PSSetShaderResources(0, 1, pTextureArray);
		pContext->Release();
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE InsertTexture(UINT glyphIndex, UINT width, UINT height, const BYTE* pTextureData) override {
		GlyphData glyphData;
		glyphData.u = 0.0f;
		glyphData.v = 0.0f;
		glyphData.sizeU = static_cast<float>(width) / static_cast<float>(m_textureSize);
		glyphData.sizeV = static_cast<float>(height) / static_cast<float>(m_textureSize);
		m_glyphDataMap[glyphIndex] = glyphData;
		if (AddTextureToAtlas(glyphIndex, width, height, pTextureData)) {
			return S_OK;
		}
		else {
			return E_FAIL;
		}
	}

	HRESULT STDMETHODCALLTYPE InsertGlyphTable(const std::vector<UINT>& glyphIndices, const std::vector<UINT>& glyphWidths, const std::vector<UINT>& glyphHeights, const std::vector<const BYTE*>& glyphTextureData) override {
		if (glyphIndices.size() != glyphWidths.size() || glyphIndices.size() != glyphHeights.size() || glyphIndices.size() != glyphTextureData.size()) {
			return E_INVALIDARG;
		}
		for (size_t i = 0; i < glyphIndices.size(); ++i) {
			HRESULT hr = InsertTexture(glyphIndices[i], glyphWidths[i], glyphHeights[i], glyphTextureData[i]);
			if (FAILED(hr)) {
				return hr;
			}
		}
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE RefreshAllAtlasWithPossibleNewGlyphs() override {
		for (size_t atlasIndex = 0; atlasIndex < m_textureArray.size(); ++atlasIndex) {
			HRESULT hr = RefreshAtlas(atlasIndex);
			if (FAILED(hr)) {
				return hr;
			}
		}
		return S_OK;
	}
private:
	ULONG m_refCount;
	ID3D11Device* m_pDevice;
	std::vector<ID3D11ShaderResourceView*> m_textureArray;
	std::map<UINT, GlyphData> m_glyphDataMap;
	UINT m_textureSize = 1024;
	bool AddTextureToAtlas(UINT glyphIndex, UINT width, UINT height, const BYTE* pTextureData) {
		// Implement the algorithm for adding the texture to an atlas here.
		// This might involve updating the atlas and/or creating new atlases as necessary.
		// Return true if the texture was added successfully, false otherwise.
	}

	HRESULT RefreshAtlas(UINT atlasIndex) {
		// Implement the algorithm for refreshing the atlas here.
		// This might involve updating the atlas with new glyph data, if necessary.
		// Return S_OK if the atlas was refreshed successfully, an error code otherwise.
	}
};

HRESULT CreateFW1GlyphAtlas(ID3D11Device* pDevice, CFW1GlyphAtlasInterface** ppGlyphAtlas) {
	if (!pDevice || !ppGlyphAtlas) {
		return E_INVALIDARG;
	}
	CFW1GlyphAtlas* pGlyphAtlas = new (std::nothrow) CFW1GlyphAtlas(pDevice);
	if (!pGlyphAtlas) {
		return E_OUTOFMEMORY;
	}

	*ppGlyphAtlas = pGlyphAtlas;
	return S_OK;
}