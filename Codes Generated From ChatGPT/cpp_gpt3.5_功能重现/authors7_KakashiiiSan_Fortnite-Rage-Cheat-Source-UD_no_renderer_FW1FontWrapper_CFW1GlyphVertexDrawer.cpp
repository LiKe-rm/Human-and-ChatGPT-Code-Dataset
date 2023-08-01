#include <d3d11.h>
#include <FW1FontWrapper.h>
#include <vector>

class CFW1GlyphVertexDrawer {
public:
	CFW1GlyphVertexDrawer();
	~CFW1GlyphVertexDrawer();

	HRESULT Initialize(ID3D11Device* pDevice, UINT vertexBufferSize);
	HRESULT DrawGlyphs(ID3D11DeviceContext* pDeviceContext, const FW1_VERTEXDATA* pVertexData);
	HRESULT DrawQuads(ID3D11DeviceContext* pDeviceContext, const FW1_VERTEXDATA* pVertexData);

private:
	ID3D11Device* m_pDevice;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	UINT m_vertexBufferSize;

	HRESULT CreateBuffers();
};

CFW1GlyphVertexDrawer::CFW1GlyphVertexDrawer()
	: m_pDevice(nullptr), m_pVertexBuffer(nullptr), m_pIndexBuffer(nullptr), m_vertexBufferSize(0) {}

CFW1GlyphVertexDrawer::~CFW1GlyphVertexDrawer() {
	if (m_pIndexBuffer) {
		m_pIndexBuffer->Release();
	}
	if (m_pVertexBuffer) {
		m_pVertexBuffer->Release();
	}
	if (m_pDevice) {
		m_pDevice->Release();
	}
}

HRESULT CFW1GlyphVertexDrawer::Initialize(ID3D11Device* pDevice, UINT vertexBufferSize) {
	if (pDevice == nullptr) {
		return E_INVALIDARG;
	}

	m_pDevice = pDevice;
	m_pDevice->AddRef();

	m_vertexBufferSize = vertexBufferSize;

	return CreateBuffers();
}

HRESULT CFW1GlyphVertexDrawer::CreateBuffers() {
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.ByteWidth = sizeof(FW1_VERTEX) * m_vertexBufferSize;
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	hr = m_pDevice->CreateBuffer(&vertexBufferDesc, nullptr, &m_pVertexBuffer);
	if (FAILED(hr)) {
		return hr;
	}

	std::vector<UINT> indices(m_vertexBufferSize * 6 / 4);
	for (size_t i = 0, j = 0; i < indices.size(); i += 6, j += 4) {
		indices[i] = j;
		indices[i + 1] = j + 1;
		indices[i + 2] = j + 2;
		indices[i + 3] = j;
		indices[i + 4] = j + 2;
		indices[i + 5] = j + 3;
	}

	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.ByteWidth = sizeof(UINT) * static_cast<UINT>(indices.size());
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA indexBufferData = {};
	indexBufferData.pSysMem = indices.data();

	hr = m_pDevice->CreateBuffer(&indexBufferDesc, &indexBufferData, &m_pIndexBuffer);

	return hr;
}

HRESULT CFW1GlyphVertexDrawer::DrawGlyphs(ID3D11DeviceContext* pDeviceContext, const FW1_VERTEXDATA* pVertexData) {
	if (pDeviceContext == nullptr || pVertexData == nullptr) {
		return E_INVALIDARG;
	}

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT hr = pDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(hr)) {
		return hr;
	}
	memcpy(mappedResource.pData, pVertexData->pVertices, pVertexData->VertexCount * sizeof(FW1_VERTEX));
	pDeviceContext->Unmap(m_pVertexBuffer, 0);

	UINT stride = sizeof(FW1_VERTEX);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pDeviceContext->DrawIndexed(pVertexData->IndexCount, 0, 0);

	return S_OK;
}

HRESULT CFW1GlyphVertexDrawer::DrawQuads(ID3D11DeviceContext* pDeviceContext, const FW1_VERTEXDATA* pVertexData) {
	if (pDeviceContext == nullptr || pVertexData == nullptr) {
		return E_INVALIDARG;
	}
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT hr = pDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(hr)) {
		return hr;
	}

	FW1_VERTEX* pDstVertices = static_cast<FW1_VERTEX*>(mappedResource.pData);
	const FW1_VERTEX* pSrcVertices = pVertexData->pVertices;
	for (UINT i = 0; i < pVertexData->VertexCount; i += 4) {
		memcpy(pDstVertices, pSrcVertices, 4 * sizeof(FW1_VERTEX));
		pDstVertices += 6;
		pSrcVertices += 4;
	}

	pDeviceContext->Unmap(m_pVertexBuffer, 0);

	UINT stride = sizeof(FW1_VERTEX);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pDeviceContext->DrawIndexed(pVertexData->IndexCount * 3 / 2, 0, 0);

	return S_OK;
}
