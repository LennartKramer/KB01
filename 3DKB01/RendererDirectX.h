#ifndef __RENDERERDIRECTX_H__
#define __RENDERERDIRECTX_H__

#include "RendererInterface.h"
#include <iostream>

class RendererDirectX 
	//: public RendererInterface
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
	void setupMatrices(D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3);
	void setupWorldMatrix(D3DXVECTOR3, D3DXVECTOR3);

	void beginScene();
	void endScene();

	void render(LPDIRECT3DTEXTURE9* g_pMeshTextures,
		LPD3DXMESH g_pMesh, int bmpWidth, int bmpHeight);

	LPDIRECT3DDEVICE9 getDevice(void);

	void initializeVertices(HWND hWnd, LPDIRECT3DDEVICE9 g_pd3dDevice,
		int bmpOffset, int bmpWidth, int bmpHeight);
	void initializeIndices(HWND hWnd, LPDIRECT3DDEVICE9 g_pd3dDevice,
		int bmpWidth, int bmpHeight);

private:
	LPDIRECT3D9             g_pD3D;
	LPDIRECT3DDEVICE9       g_pd3dDevice;
	LPDIRECT3DINDEXBUFFER9  g_pIB;
	LPDIRECT3DVERTEXBUFFER9 g_pVB;
	LPDIRECT3DTEXTURE9		g_pTexture;

	Vertex_TD *vertex_Vertices;
};

#endif