#include <d3d9.h>
#include <d3dx9.h>
#include "imgui.h"
#include "imgui_impl_dx9.h"

struct ImGui_ImplDX9_Data {
    IDirect3DDevice9* device;
    IDirect3DVertexBuffer9* vertex_buffer;
    IDirect3DIndexBuffer9* index_buffer;
    IDirect3DTexture9* font_texture;
    int vertex_buffer_size;
    int index_buffer_size;
};

struct CUSTOMVERTEX {
    float pos[3];
    D3DCOLOR col;
    float uv[2];
};

ImGui_ImplDX9_Data* ImGui_ImplDX9_GetBackendData() {
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplDX9_Data* backend_data = (ImGui_ImplDX9_Data*)io.BackendRendererUserData;
    return backend_data;
}

void ImGui_ImplDX9_SetupRenderState(ImDrawData* draw_data) {
    ImGui_ImplDX9_Data* data = ImGui_ImplDX9_GetBackendData();
    IDirect3DDevice9* device = data->device;
    ImGuiIO& io = ImGui::GetIO();

    // Set up viewport
    D3DVIEWPORT9 vp;
    vp.X = vp.Y = 0;
    vp.Width = (DWORD)io.DisplaySize.x;
    vp.Height = (DWORD)io.DisplaySize.y;
    vp.MinZ = 0.0f;
    vp.MaxZ = 1.0f;
    device->SetViewport(&vp);

    // Set render mode
    device->SetPixelShader(NULL);
    device->SetVertexShader(NULL);
    device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    device->SetRenderState(D3DRS_LIGHTING, false);
    device->SetRenderState(D3DRS_ZENABLE, false);
    device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
    device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
    device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    device->SetRenderState(D3DRS_SCISSORTESTENABLE, true);

    // Set up orthographic projection matrix for 2D rendering
    D3DXMATRIXA16 mat_proj;
    D3DXMatrixOrthoOffCenterLH(&mat_proj, 0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f, -1.0f, 1.0f);
    device->SetTransform(D3DTS_PROJECTION, &mat_proj);

    device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
}

void ImGui_ImplDX9_RenderDrawData(ImDrawData* draw_data) {
    ImGui_ImplDX9_Data* data = ImGui_ImplDX9_GetBackendData();
    IDirect3DDevice9* device = data->device;

    // Backup current DirectX 9 state
    IDirect3DStateBlock9* d3d9_state_block = NULL;
    if (device->CreateStateBlock(D3DSBT_ALL, &d3d9_state_block) < 0)
        return;

    // Set up scissor rect
    RECT rect;
    GetClientRect(GetForegroundWindow(), &rect);
    device->SetScissorRect(&rect);

    // Set up ImGui render state
    ImGui_ImplDX9_SetupRenderState(draw_data);

    // Render geometry based on ImGui command lists
    for (int n = 0; n < draw_data->CmdListsCount; n++) {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        const ImDrawIdx* idx_buffer_offset = 0;

        // Copy ImGui vertex data to DirectX 9 buffers
        CUSTOMVERTEX* vtx_dst;
        ImDrawIdx* idx_dst;
        if (data->vertex_buffer->Lock(0, (UINT)(cmd_list->VtxBuffer.Size * sizeof(CUSTOMVERTEX)), (void**)&vtx_dst, 0) != D3D_OK)
        return;
    if (data->index_buffer->Lock(0, (UINT)(cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx)), (void**)&idx_dst, 0) != D3D_OK)
        return;

    for (int i = 0; i < cmd_list->VtxBuffer.Size; i++) {
        vtx_dst[i].pos[0] = cmd_list->VtxBuffer[i].pos.x;
        vtx_dst[i].pos[1] = cmd_list->VtxBuffer[i].pos.y;
        vtx_dst[i].pos[2] = 0.0f;
        vtx_dst[i].col = (cmd_list->VtxBuffer[i].col & 0xFF00FF00) | ((cmd_list->VtxBuffer[i].col & 0xFF0000) >> 16) | ((cmd_list->VtxBuffer[i].col & 0xFF) << 16); // RGBA --> ARGB
        vtx_dst[i].uv[0] = cmd_list->VtxBuffer[i].uv.x;
        vtx_dst[i].uv[1] = cmd_list->VtxBuffer[i].uv.y;
    }
    memcpy(idx_dst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));

    data->vertex_buffer->Unlock();
    data->index_buffer->Unlock();

    device->SetStreamSource(0, data->vertex_buffer, 0, sizeof(CUSTOMVERTEX));
    device->SetIndices(data->index_buffer);

    for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++) {
        const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
        if (pcmd->UserCallback) {
            pcmd->UserCallback(cmd_list, pcmd);
        } else {
            const RECT r = {(LONG)pcmd->ClipRect.x, (LONG)pcmd->ClipRect.y, (LONG)pcmd->ClipRect.z, (LONG)pcmd->ClipRect.w};
            device->SetTexture(0, (LPDIRECT3DTEXTURE9)pcmd->TextureId);
            device->SetScissorRect(&r);
            device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, (UINT)cmd_list->VtxBuffer.Size, idx_buffer_offset, pcmd->ElemCount / 3);
        }
        idx_buffer_offset += pcmd->ElemCount;
    }
}

// Restore the backed-up state
d3d9_state_block->Apply();
d3d9_state_block->Release();

