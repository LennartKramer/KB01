#ifndef __RENDERERDIRECTX_H__
#define __RENDERERDIRECTX_H__

#include "RendererInterface.h"

class RendererDirectX 
	// : public RendererInterface
{
public:
	RendererDirectX(void);
	~RendererDirectX(void);

	HRESULT initD3D(HWND hWndw);
	HRESULT initGeometry(void);
	LRESULT WINAPI msgProc(HWND hWnd, UINT msg, 
		WPARAM wParam, LPARAM lParam);
	INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE,
		LPWSTR, int);

	void cleanUp(void);
	void setupMatrices(void);
	void render(D3DMATERIAL9* g_pMeshMaterials, LPDIRECT3DTEXTURE9* g_pMeshTextures,
		DWORD g_dwNumMaterials, LPD3DXMESH g_pMesh);
	LPDIRECT3DDEVICE9 getDevice(void);
private:
	LPDIRECT3D9             g_pD3D;
	LPDIRECT3DDEVICE9       g_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9 g_pVB;
	LPDIRECT3DTEXTURE9		g_pTexture;
};

#endif