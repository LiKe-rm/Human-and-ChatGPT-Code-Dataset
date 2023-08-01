#include <D3D11.h>
#include <wrl/client.h>
#include <stdexcept>

class CFW1StateSaver {
public:
	CFW1StateSaver();
	~CFW1StateSaver();

	HRESULT Save(ID3D11DeviceContext* pDeviceContext);
	HRESULT Restore();
	void ReleaseSavedStates();

private:
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_pRasterizerState;
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_pBlendState;
	FLOAT m_BlendFactor[4];
	UINT m_SampleMask;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_pDepthStencilState;
	UINT m_StencilRef;
	D3D11_PRIMITIVE_TOPOLOGY m_Topology;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pShaderResourceView;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_pSamplerState;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pVertexShader;
};

CFW1StateSaver::CFW1StateSaver() {
	memset(&m_BlendFactor, 0, sizeof(m_BlendFactor));
	m_SampleMask = 0xFFFFFFFF;
	m_StencilRef = 0;
	m_Topology = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
}

CFW1StateSaver::~CFW1StateSaver() {
	ReleaseSavedStates();
}

HRESULT CFW1StateSaver::Save(ID3D11DeviceContext* pDeviceContext) {
	if (!pDeviceContext) {
		return E_INVALIDARG;
	}

	ReleaseSavedStates();

	pDeviceContext->RSGetState(m_pRasterizerState.ReleaseAndGetAddressOf());
	pDeviceContext->OMGetBlendState(m_pBlendState.ReleaseAndGetAddressOf(), m_BlendFactor, &m_SampleMask);
	pDeviceContext->OMGetDepthStencilState(m_pDepthStencilState.ReleaseAndGetAddressOf(), &m_StencilRef);
	pDeviceContext->IAGetPrimitiveTopology(&m_Topology);
	pDeviceContext->IAGetInputLayout(m_pInputLayout.ReleaseAndGetAddressOf());
	pDeviceContext->PSGetShaderResources(0, 1, m_pShaderResourceView.ReleaseAndGetAddressOf());
	pDeviceContext->PSGetSamplers(0, 1, m_pSamplerState.ReleaseAndGetAddressOf());
	pDeviceContext->PSGetShader(m_pPixelShader.ReleaseAndGetAddressOf(), nullptr, 0);
	pDeviceContext->VSGetShader(m_pVertexShader.ReleaseAndGetAddressOf(), nullptr, 0);

	return S_OK;
}

HRESULT CFW1StateSaver::Restore() {
	if (!m_pRasterizerState) {
		return E_FAIL;
	}

	ID3D11DeviceContext* pDeviceContext = nullptr;
	m_pRasterizerState->GetDevice(&pDeviceContext);
	if (!pDeviceContext) {
		return E_FAIL;
	}

	pDeviceContext->RSSetState(m_pRasterizerState.Get());
	pDeviceContext->OMSetBlendState(m_pBlendState.Get(), m_BlendFactor, m_SampleMask);
	pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState.Get(), m_StencilRef);
	pDeviceContext->IASetPrimitiveTopology(m_Topology);
	pDeviceContext->IASetInputLayout(m_pInputLayout.Get());
	pDeviceContext->PSSetShaderResources(0, 1, m_pShaderResourceView.GetAddressOf());
	pDeviceContext->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());
	pDeviceContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);
	pDeviceContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
	pDeviceContext->Release();
	return S_OK;
}

void CFW1StateSaver::ReleaseSavedStates() {
	m_pRasterizerState.Reset();
	m_pBlendState.Reset();
	memset(&m_BlendFactor, 0, sizeof(m_BlendFactor));
	m_SampleMask = 0xFFFFFFFF;
	m_pDepthStencilState.Reset();
	m_StencilRef = 0;
	m_Topology = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
	m_pInputLayout.Reset();
	m_pShaderResourceView.Reset();
	m_pSamplerState.Reset();
	m_pPixelShader.Reset();
	m_pVertexShader.Reset();
}
