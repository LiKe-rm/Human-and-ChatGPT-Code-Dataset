#include <d3d11.h>
#include <wrl/client.h>

class no_state_saver
{
public:
    no_state_saver(ID3D11DeviceContext* device_context)
        : m_device_context(device_context)
    {
        // 初始化所有的状态成员变量
        m_blend_state.Reset();
        m_rasterizer_state.Reset();
        m_depth_stencil_state.Reset();
        m_vertex_shader.Reset();
        m_geometry_shader.Reset();
        m_pixel_shader.Reset();
    }

    ~no_state_saver()
    {
        // 释放保存的状态
        release_saved_state();
    }

    void save_current_state()
    {
        // 保存当前的渲染状态
        m_device_context->OMGetBlendState(m_blend_state.GetAddressOf(), m_blend_factor, &m_sample_mask);
        m_device_context->RSGetState(m_rasterizer_state.GetAddressOf());
        m_device_context->OMGetDepthStencilState(m_depth_stencil_state.GetAddressOf(), &m_stencil_ref);
        m_device_context->VSGetShader(m_vertex_shader.GetAddressOf(), nullptr, nullptr);
        m_device_context->GSGetShader(m_geometry_shader.GetAddressOf(), nullptr, nullptr);
        m_device_context->PSGetShader(m_pixel_shader.GetAddressOf(), nullptr, nullptr);
    }

    void restore_saved_state()
    {
        // 恢复保存的渲染状态
        m_device_context->OMSetBlendState(m_blend_state.Get(), m_blend_factor, m_sample_mask);
        m_device_context->RSSetState(m_rasterizer_state.Get());
        m_device_context->OMSetDepthStencilState(m_depth_stencil_state.Get(), m_stencil_ref);
        m_device_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
        m_device_context->GSSetShader(m_geometry_shader.Get(), nullptr, 0);
        m_device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
    }

    void release_saved_state()
    {
        // 释放保存的状态并将所有状态成员变量重置为默认值
        m_blend_state.Reset();
        m_rasterizer_state.Reset();
        m_depth_stencil_state.Reset();
        m_vertex_shader.Reset();
        m_geometry_shader.Reset();
        m_pixel_shader.Reset();
    }

private:
    ID3D11DeviceContext* m_device_context;
    Microsoft::WRL::ComPtr<ID3D11BlendState> m_blend_state;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizer_state;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depth_stencil_state;
    Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertex_shader;
    Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometry_shader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixel_shader;
    FLOAT m_blend_factor[4];
    UINT m_sample_mask;
    UINT m_stencil_ref;
};
