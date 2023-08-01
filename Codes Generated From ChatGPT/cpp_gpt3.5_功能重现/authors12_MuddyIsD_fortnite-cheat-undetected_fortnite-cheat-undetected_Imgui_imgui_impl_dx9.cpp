#include <d3d9.h>
#include <d3dx9.h>
#include "imgui.h"
#include "imgui_impl_dx9.h"

struct CUSTOMVERTEX
{
	float pos[3];
	float uv[2];
	DWORD col;
};

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// Global variables
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static LPDIRECT3DVERTEXBUFFER9  g_pVB = NULL;
static LPDIRECT3DINDEXBUFFER9   g_pIB = NULL;
static LPDIRECT3DTEXTURE9       g_pFontTexture = NULL;

// Renderer functions
bool ImGui_ImplDX9_Init(LPDIRECT3DDEVICE9 device)
{
	if (!device)
		return false;

	g_pd3dDevice = device;

	ImGuiIO& io = ImGui::GetIO();

	io.BackendRendererName = "imgui_impl_dx9";
	io.ImGui_ImplDX9_CreateDeviceObjects();

	return true;
}

void ImGui_ImplDX9_Shutdown()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	g_pd3dDevice = NULL;
}

void ImGui_ImplDX9_InvalidateDeviceObjects()
{
	if (!g_pd3dDevice)
		return;

	if (g_pVB)
	{
		g_pVB->Release();
		g_pVB = NULL;
	}

	if (g_pIB)
	{
		g_pIB->Release();
		g_pIB = NULL;
	}

	ImGuiIO& io = ImGui::GetIO();
	if (g_pFontTexture)
	{
		io.Fonts->TexID = NULL;
		g_pFontTexture->Release();
		g_pFontTexture = NULL;
	}
}

bool ImGui_ImplDX9_CreateDeviceObjects()
{
	if (!g_pd3dDevice)
		return false;

	// Create vertex buffer
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, CUSTOMFVF, D3DPOOL_DEFAULT, &g_pVB, NULL)))
		return false;

	// Create index buffer
	if (FAILED(g_pd3dDevice->CreateIndexBuffer(6 * sizeof(ImDrawIdx), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, sizeof(ImDrawIdx) == 2 ? D3DFMT_INDEX16 : D3DFMT_INDEX32, D3DPOOL_DEFAULT, &g_pIB, NULL)))
		return false;

	// Create font texture
	ImGuiIO& io = ImGui::GetIO();
	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
	if (FAILED(g_pd3dDevice->CreateTexture(width, height, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_pFontTexture, NULL)))
		return false;

	// Upload font texture
	D3DLOCKED_RECT tex_locked_rect;
	if (g_pFontTexture->LockRect(0, &tex_locked_rect, NULL, 0) != D3D_OK)
		return false;
	for (int y = 0; y < height; y++)
		memcpy((unsigned char*)tex_locked_rect.pBits + tex_locked_rect.Pitch * y, pixels + (size_t)width * 4 * y, (size_t)width * 4);
	g_pFontTexture->UnlockRect(0);
	// Store font texture pointer
	io.Fonts->TexID = (ImTextureID)g_pFontTexture;

	return true;
}

void ImGui_ImplDX9_RenderDrawData(ImDrawData* draw_data)
{
	if (!g_pd3dDevice)
		return;
	// Backup the DX9 state
	IDirect3DStateBlock9* d3d9_state_block = NULL;
	if (g_pd3dDevice->CreateStateBlock(D3DSBT_ALL, &d3d9_state_block) < 0)
		return;

	// Setup render state: fixed-pipeline, alpha-blending, no face culling, no depth testing, shade mode (for gradient)
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	g_pd3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	g_pd3dDevice->SetRenderState(D3DRS_FOGENABLE, false);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// Setup orthographic projection matrix
	D3DXMATRIXA16 mat_projection;
	D3DXMatrixIdentity(&mat_projection);
	mat_projection._11 = 2.0f / draw_data->DisplaySize.x;
	mat_projection._22 = 2.0f / draw_data->DisplaySize.y;
	mat_projection._41 = -1.0f - draw_data->DisplayPos.x * mat_projection._11;
	mat_projection._42 = -1.0f - draw_data->DisplayPos.y * mat_projection._22;
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &mat_projection);
	// Loop through all command lists
	for (int n = 0; n < draw_data->CmdListsCount; n++)
	{
		const ImDrawList* cmd_list = draw_data->CmdLists[n];
		const ImDrawVert* vtx_buffer = cmd_list->VtxBuffer.Data;
		const ImDrawIdx* idx_buffer = cmd_list->IdxBuffer.Data;

		// Upload vertex/index buffers
		void* vertices;
		if (g_pVB->Lock(0, (UINT)(cmd_list->VtxBuffer.Size * sizeof(ImDrawVert)), &vertices, D3DLOCK_DISCARD) != D3D_OK)
			return;
		memcpy(vertices, vtx_buffer, (size_t)cmd_list->VtxBuffer.Size * sizeof(ImDrawVert));
		g_pVB->Unlock();

		void* indices;
		if (g_pIB->Lock(0, (UINT)(cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx)), &indices, D3DLOCK_DISCARD) != D3D_OK)
			return;
		memcpy(indices, idx_buffer, (size_t)cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
		g_pIB->Unlock();

		g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(ImDrawVert));
		g_pd3dDevice->SetIndices(g_pIB);
		g_pd3dDevice->SetFVF(CUSTOMFVF);

		// Render command lists
		int idx_offset = 0;
		for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
		{
			const ImDrawCmd* cmd = &cmd_list->CmdBuffer[cmd_i];
			if (cmd->UserCallback)
			{
				cmd->UserCallback(cmd_list, cmd);
			}
			else
			{
				const RECT r = { (LONG)cmd->ClipRect.x, (LONG)cmd->ClipRect.y, (LONG)cmd->ClipRect.z, (LONG)cmd->ClipRect.w };
				g_pd3dDevice->SetTexture(0, (LPDIRECT3DTEXTURE9)cmd->TextureId);
				g_pd3dDevice->SetScissorRect(&r);
				g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, (UINT)cmd_list->VtxBuffer.Size, idx_offset, cmd->ElemCount / 3);
			}
			idx_offset += cmd->ElemCount;
		}
	}

	// Restore the DX9 state
	d3d9_state_block->Apply();
	d3d9_state_block->Release();
}

