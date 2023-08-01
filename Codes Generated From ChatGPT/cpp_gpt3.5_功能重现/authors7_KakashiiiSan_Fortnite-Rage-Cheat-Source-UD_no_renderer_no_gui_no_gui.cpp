#include <d3d11.h>
#include <d3dx11.h>
#include <D3DX10math.h>
#include <string>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

class NoGUI {
public:
	HRESULT init(HWND hWnd);
	void reset();
	void fill_rect(FLOAT x, FLOAT y, FLOAT width, FLOAT height, D3DXCOLOR color);
	void draw_string(const std::wstring& text, FLOAT x, FLOAT y, FLOAT size, D3DXCOLOR color);
	void draw_line(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, D3DXCOLOR color);
	void draw_rect(FLOAT x, FLOAT y, FLOAT width, FLOAT height, D3DXCOLOR color);
	void draw_outlined_rect(FLOAT x, FLOAT y, FLOAT width, FLOAT height, D3DXCOLOR color, FLOAT outline_thickness);
	void draw_corner_box(FLOAT x, FLOAT y, FLOAT width, FLOAT height, D3DXCOLOR color, FLOAT corner_size);
	void draw_border(FLOAT x, FLOAT y, FLOAT width, FLOAT height, D3DXCOLOR color, FLOAT border_thickness);
	void draw_cross(FLOAT x, FLOAT y, FLOAT size, D3DXCOLOR color);
	void draw_circle(FLOAT x, FLOAT y, FLOAT radius, D3DXCOLOR color, FLOAT thickness);

private:
	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_device_context = nullptr;
	IDXGISwapChain* m_swap_chain = nullptr;
	ID3D11RenderTargetView* m_render_target_view = nullptr;

	ID3D11VertexShader* m_vertex_shader = nullptr;
	ID3D11PixelShader* m_pixel_shader = nullptr;
	ID3D11InputLayout* m_input_layout = nullptr;
	ID3D11Buffer* m_vertex_buffer = nullptr;
	ID3D11Buffer* m_index_buffer = nullptr;

	ID3D11Buffer* m_constant_buffer = nullptr;

	struct Vertex {
		D3DXVECTOR3 position;
		D3DXCOLOR color;
	};

	struct ConstantBuffer {
		D3DXMATRIX mWorld;
		D3DXMATRIX mView;
		D3DXMATRIX mProjection;
	};

	HRESULT create_device_and_swap_chain(HWND hWnd);
	HRESULT create_render_target_view();
	HRESULT create_vertex_and_pixel_shaders();
	HRESULT create_input_layout();
	HRESULT create_vertex_and_index_buffers();
	HRESULT create_constant_buffer();

	void release_resources();
};

HRESULT NoGUI::init(HWND hWnd) {
	if (FAILED(create_device_and_swap_chain(hWnd))) {
		return E_FAIL;
	}

	if (FAILED(create_render_target_view())) {
		return E_FAIL;
	}

	if (FAILED(create_vertex_and_pixel_shaders())) {
		return E_FAIL;
	}

	if (FAILED(create_input_layout())) {
		return E_FAIL;
	}

	if (FAILED(create_vertex_and_index_buffers())) {
		return E_FAIL;
	}

	if (FAILED(create_constant_buffer())) {
		return E_FAIL;
	}

	return S_OK;
}

void NoGUI::reset() {
	release_resources();
}

// Implement fill_rect, draw_string, draw_line, draw_rect, draw_outlined_rect, draw_corner_box, draw_border, draw_cross, and draw_circle here.

HRESULT NoGUI::create_device_and_swap_chain(HWND hWnd) {
	// Initialize DXGI_SWAP_CHAIN_DESC structure
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = 800;

	sd.BufferDesc.Height = 600;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0
	};
	D3D_FEATURE_LEVEL featureLevel;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		featureLevels,
		1,
		D3D11_SDK_VERSION,
		&sd,
		&m_swap_chain,
		&m_device,
		&featureLevel,
		&m_device_context
	);

	return hr;
}

HRESULT NoGUI::create_render_target_view() {
	HRESULT hr;
	ID3D11Texture2D* backBuffer = nullptr;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	if (FAILED(hr)) {
		return hr;
	}

	hr = m_device->CreateRenderTargetView(backBuffer, nullptr, &m_render_target_view);
	backBuffer->Release();

	return hr;
}

HRESULT NoGUI::create_vertex_and_pixel_shaders() {
	// Vertex shader
	static const char* vertexShaderSource =
		"struct VS_INPUT
	{
		float4 Pos : POSITION;
		float4 Color : COLOR;
	};
	struct PS_INPUT
	{
		float4 Pos : SV_POSITION;
		float4 Color : COLOR;
	};
	PS_INPUT VS(VS_INPUT input)
	{
		PS_INPUT output;
		output.Pos = input.Pos;
		output.Color = input.Color;
		return output;
	}";
		HRESULT hr = m_device->CreateVertexShader(vertexShaderSource, strlen(vertexShaderSource), nullptr, &m_vertex_shader);
	if (FAILED(hr)) {
		return hr;
	}

	// Pixel shader
	static const char* pixelShaderSource =
		"struct PS_INPUT\
    {\
        float4 Pos : SV_POSITION;\
        float4 Color : COLOR;\
    };\
    float4 PS(PS_INPUT input) : SV_Target\
    {\
        return input.Color;\
    }";

	hr = m_device->CreatePixelShader(pixelShaderSource, strlen(pixelShaderSource), nullptr, &m_pixel_shader);

	return hr;
}

HRESULT NoGUI::create_input_layout() {
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	HRESULT hr = m_device->CreateInputLayout(inputElementDesc, 2, &m_vertex_shader, sizeof(m_vertex_shader), &m_input_layout);

	return hr;
}

HRESULT NoGUI::create_vertex_and_index_buffers() {
	// Vertex buffer
	Vertex vertices[] = {
	{D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},
	{D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},
	{D3DXVECTOR3(1.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},
	{D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)}
	};
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	HRESULT hr = m_device->CreateBuffer(&bd, &vertexData, &m_vertex_buffer);
	if (FAILED(hr)) {
		return hr;
	}

	// Index buffer
	UINT indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(UINT) * 6;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	hr = m_device->CreateBuffer(&bd, &indexData, &m_index_buffer);

	return hr;
}

HRESULT NoGUI::create_constant_buffer() {
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	HRESULT hr = m_device->CreateBuffer(&bd, nullptr, &m_constant_buffer);

	return hr;
}

void NoGUI::release_resources() {
	if (m_device) m_device->Release();
	if (m_device_context) m_device_context->Release();
	if (m_swap_chain) m_swap_chain->Release();
	if (m_render_target_view) m_render_target_view->Release();
	if (m_vertex_shader) m_vertex_shader->Release();
	if (m_pixel_shader) m_pixel_shader->Release();
	if (m_input_layout) m_input_layout->Release();
	if (m_vertex_buffer) m_vertex_buffer->Release();
	if (m_index_buffer) m_index_buffer->Release();
	if (m_constant_buffer) m_constant_buffer->Release();
}

// Implement the fill_rect, draw_string, draw_line, draw_rect, draw_outlined_rect, draw_corner_box, draw_border, draw_cross, and draw_circle methods here.

int main() {
	// This is just a placeholder to demonstrate how to use the class.
	// Please replace this with your own application entry point and properly initialize the NoGUI class.
	NoGUI noGUI;
	HWND hWnd = nullptr;
	if (noGUI.init(hWnd) == S_OK) {
		// Perform your rendering tasks here
		// Example:
		// noGUI.fill_rect(10.0f, 20.0f, 100.0f, 50.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		// noGUI.draw_string(L"Hello, world!", 10.0f, 10.0f, 24.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			// After finishing your tasks, release the resources
		noGUI.reset();
	}

	return 0;

}