#include <d3d11.h>
#include <FW1FontWrapper.h>
#include <vector>
#include <unordered_map>

class CFW1GlyphSheet : public IFW1GlyphSheet {
public:
	CFW1GlyphSheet();
	virtual ~CFW1GlyphSheet();

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject);
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();

	HRESULT STDMETHODCALLTYPE Initialize(ID3D11Device* pDevice, UINT width, UINT height);
	HRESULT STDMETHODCALLTYPE InsertGlyph(FW1_GLYPHIMAGEDATA* pGlyphData, UINT* pSheetX, UINT* pSheetY);
	HRESULT STDMETHODCALLTYPE GetSheetInfo(FW1_GLYPHSHEETINFO* pSheetInfo);
	HRESULT STDMETHODCALLTYPE BindSheet(ID3D11DeviceContext* pDeviceContext, UINT slot);
	HRESULT STDMETHODCALLTYPE CloseSheet();
	HRESULT STDMETHODCALLTYPE RefreshSheet();

private:
	ULONG m_cRefCount;

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	ID3D11Texture2D* m_pTexture;
	ID3D11ShaderResourceView* m_pSRV;

	UINT m_width;
	UINT m_height;
	UINT m_currentX;
	UINT m_currentY;
	UINT m_nextY;
	bool m_isClosed;

	std::unordered_map<UINT, std::pair<UINT, UINT>> m_glyphMap;
	std::vector<BYTE> m_textureData;

	HRESULT CreateTexture();
};

CFW1GlyphSheet::CFW1GlyphSheet() :
	m_cRefCount(1),
	m_pDevice(nullptr),
	m_pDeviceContext(nullptr),
	m_pTexture(nullptr),
	m_pSRV(nullptr),
	m_width(0),
	m_height(0),
	m_currentX(0),
	m_currentY(0),
	m_nextY(0),
	m_isClosed(false)
{}

CFW1GlyphSheet::~CFW1GlyphSheet() {
	if (m_pSRV) m_pSRV->Release();
	if (m_pTexture) m_pTexture->Release();
	if (m_pDeviceContext) m_pDeviceContext->Release();
	if (m_pDevice) m_pDevice->Release();
}

HRESULT STDMETHODCALLTYPE CFW1GlyphSheet::QueryInterface(REFIID riid, void** ppvObject) {
	if (!ppvObject) return E_INVALIDARG;
	if (riid == __uuidof(IUnknown) || riid == __uuidof(IFW1GlyphSheet)) {
		*ppvObject = this;
		AddRef();
		return S_OK;
	}
	*ppvObject = nullptr;
	return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE CFW1GlyphSheet::AddRef() {
	return ++m_cRefCount;
}

ULONG STDMETHODCALLTYPE CFW1GlyphSheet::Release() {
	ULONG newCount = --m_cRefCount;
	if (newCount == 0) delete this;
	return newCount;
}

HRESULT STDMETHODCALLTYPE CFW1GlyphSheet::Initialize(ID3D11Device* pDevice, UINT width, UINT height) {
	if (!pDevice) return E_INVALIDARG;
	pDevice->AddRef();
	m_pDevice = pDevice;

	pDevice->GetImmediateContext(&m_pDeviceContext);

	m_width = width;
	m_height = height;
	m_textureData.resize(width * height, 0);

	return CreateTexture();
}

HRESULT STDMETHODCALLTYPE CFW1GlyphSheet::InsertGlyph(FW1_GLYPHIMAGEDATA* pGlyphData, UINT* pSheetX, UINT* pSheetY) {
	if (m_isClosed || !pGlyphData) return E_INVALIDARG;
	UINT glyphWidth = pGlyphData->Width + 1;
	UINT glyphHeight = pGlyphData->Height + 1;

	if (glyphWidth > m_width || glyphHeight > m_height) return E_FAIL;

	if (m_currentX + glyphWidth > m_width) {
		m_currentX = 0;
		m_currentY = m_nextY;
	}

	if (m_currentY + glyphHeight > m_height) return E_FAIL;

	for (UINT y = 0; y < glyphHeight - 1; ++y) {
		for (UINT x = 0; x < glyphWidth - 1; ++x) {
			m_textureData[(m_currentY + y) * m_width + (m_currentX + x)] = pGlyphData->pImageData[y * pGlyphData->Width + x];
		}
	}

	m_glyphMap[pGlyphData->GlyphIndex] = std::make_pair(m_currentX, m_currentY);

	if (pSheetX) *pSheetX = m_currentX;
	if (pSheetY) *pSheetY = m_currentY;

	m_currentX += glyphWidth;
	m_nextY = std::max(m_nextY, m_currentY + glyphHeight);

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CFW1GlyphSheet::GetSheetInfo(FW1_GLYPHSHEETINFO* pSheetInfo) {
	if (!pSheetInfo) return E_INVALIDARG;
	pSheetInfo->Width = m_width;
	pSheetInfo->Height = m_height;
	pSheetInfo->GlyphCount = static_cast<UINT>(m_glyphMap.size());

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CFW1GlyphSheet::BindSheet(ID3D11DeviceContext* pDeviceContext, UINT slot) {
	if (!pDeviceContext) return E_INVALIDARG;
	pDeviceContext->PSSetShaderResources(slot, 1, &m_pSRV);

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CFW1GlyphSheet::CloseSheet() {
	m_isClosed = true;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CFW1GlyphSheet::RefreshSheet() {
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT hr = m_pDeviceContext->Map(m_pTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(hr)) return hr;
	BYTE* pDestData = static_cast<BYTE*>(mappedResource.pData);
	for (UINT y = 0; y < m_height; ++y) {
		memcpy(pDestData, &m_textureData[y * m_width], m_width);
		pDestData += mappedResource.RowPitch;
	}

	m_pDeviceContext->Unmap(m_pTexture, 0);

	return S_OK;
}

HRESULT CFW1GlyphSheet::CreateTexture() {
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = m_width;
	desc.Height = m_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = m_pDevice->CreateTexture2
		D(&desc, nullptr, &m_pTexture);
	if (FAILED(hr)) return hr;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));

	srvDesc.Format = desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;

	hr = m_pDevice->CreateShaderResourceView(m_pTexture, &srvDesc, &m_pSRV);
	if (FAILED(hr)) {
		m_pTexture->Release();
		m_pTexture = nullptr;
		return hr;
	}

	return S_OK;
}
