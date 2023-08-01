#include <d3d11.h>
#include <FW1FontWrapper.h>
#include "CFW1GlyphRenderStatesInterface.h"

class CFW1GlyphRenderStates : public IFW1GlyphRenderStates {
public:
	CFW1GlyphRenderStates();
	virtual ~CFW1GlyphRenderStates();

	// IUnknown methods
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject);
	virtual ULONG STDMETHODCALLTYPE AddRef();
	virtual ULONG STDMETHODCALLTYPE Release();

	// IFW1GlyphRenderStates methods
	virtual HRESULT STDMETHODCALLTYPE GetDevice(ID3D11Device** ppDevice);
	virtual void STDMETHODCALLTYPE SetStates(UINT32 Flags);
	virtual void STDMETHODCALLTYPE UpdateShaderConstants(const float* pTransformMatrix, const float* pClipRect);
	virtual BOOL STDMETHODCALLTYPE HasGeometryShader();

private:
	ULONG m_cRefCount;
	ID3D11Device* m_pDevice;
	ID3D11InputLayout* m_pInputLayout;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11GeometryShader* m_pGeometryShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11BlendState* m_pBlendState;
	ID3D11DepthStencilState* m_pDepthStencilState;
	ID3D11RasterizerState* m_pRasterizerState;
	ID3D11SamplerState* m_pSamplerState;
	ID3D11Buffer* m_pConstantBuffer;

	HRESULT InitStates();
	void ReleaseStates();
};

CFW1GlyphRenderStates::CFW1GlyphRenderStates()
	: m_cRefCount(1),
	m_pDevice(nullptr),
	m_pInputLayout(nullptr),
	m_pVertexShader(nullptr),
	m_pGeometryShader(nullptr),
	m_pPixelShader(nullptr),
	m_pBlendState(nullptr),
	m_pDepthStencilState(nullptr),
	m_pRasterizerState(nullptr),
	m_pSamplerState(nullptr),
	m_pConstantBuffer(nullptr) {
}

CFW1GlyphRenderStates::~CFW1GlyphRenderStates() {
	ReleaseStates();
}

HRESULT STDMETHODCALLTYPE CFW1GlyphRenderStates::QueryInterface(REFIID riid, void** ppvObject) {
	if (!ppvObject) return E_POINTER;
	if (riid == __uuidof(IUnknown) || riid == __uuidof(IFW1GlyphRenderStates)) {
		*ppvObject = static_cast<IFW1GlyphRenderStates*>(this);
		AddRef();
		return S_OK;
	}
	*ppvObject = nullptr;
	return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE CFW1GlyphRenderStates::AddRef() {
	return InterlockedIncrement(&m_cRefCount);
}

ULONG STDMETHODCALLTYPE CFW1GlyphRenderStates::Release() {
	ULONG newRefCount = InterlockedDecrement(&m_cRefCount);
	if (newRefCount == 0) {
		delete this;
	}
	return newRefCount;
}

HRESULT STDMETHODCALLTYPE CFW1GlyphRenderStates::GetDevice(ID3D11Device** ppDevice) {
	if (!ppDevice) return E_POINTER;
	*ppDevice = m_pDevice;
	if (m_pDevice) m_pDevice->AddRef();
	return S_OK;
}

void STDMETHODCALLTYPE CFW1GlyphRenderStates::SetStates(UINT32 Flags) {
	// Implement the SetStates function to set the required render states
}

void STDMETHODCALLTYPE CFW1GlyphRenderStates::UpdateShaderConstants(const float* pTransformMatrix, const float* pClipRect) {
	// Implement the UpdateShaderConstants function to update the shader constants
}

BOOL STDMETHODCALLTYPE CFW1GlyphRenderStates::HasGeometryShader() {
	return (m_pGeometryShader != nullptr);
}

HRESULT CFW1GlyphRenderStates::InitStates() {
	// Implement the InitStates function to initialize the required render states
}

void CFW1GlyphRenderStates::ReleaseStates() {
	if (m_pInputLayout) m_pInputLayout->Release();
	if (m_pVertexShader) m_pVertexShader->Release();
	if (m_pGeometryShader) m_pGeometryShader->Release();
	if (m_pPixelShader) m_pPixelShader->Release();
	if (m_pBlendState) m_pBlendState->Release();
	if (m_pDepthStencilState) m_pDepthStencilState->Release();
	if (m_pRasterizerState) m_pRasterizerState->Release();
	if (m_pSamplerState) m_pSamplerState->Release();
	if (m_pConstantBuffer) m_pConstantBuffer->Release();
	m_pInputLayout = nullptr;
	m_pVertexShader = nullptr;
	m_pGeometryShader = nullptr;
	m_pPixelShader = nullptr;
	m_pBlendState = nullptr;
	m_pDepthStencilState = nullptr;
	m_pRasterizerState = nullptr;
	m_pSamplerState = nullptr;
	m_pConstantBuffer = nullptr;
}
