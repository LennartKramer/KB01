#ifndef __RENDERERDIRECTX_H__
#define __RENDERERDIRECTX_H__

#include "RendererInterface.h"

class RendererDirectX
	//: public RendererInterface
{
public:
	RendererDirectX();
	~RendererDirectX();

	HRESULT initD3D(HWND hWndw);
	HRESULT initGeometry();
	LRESULT WINAPI msgProc(HWND hWnd, UINT msg, 
		WPARAM wParam, LPARAM lParam);
	int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE,
		LPWSTR, int);

	void cleanUp();
	void setupMatrices();
	void render();

protected:
	LPDIRECT3D9             g_pD3D;
	LPDIRECT3DDEVICE9       g_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9 g_pVB;
	LPDIRECT3DTEXTURE9		g_pTexture;
};

#endif