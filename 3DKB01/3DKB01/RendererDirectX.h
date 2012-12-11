#ifndef __RENDERERDIRECTX_H__
#define __RENDERERDIRECTX_H__

#include "RendererInterface.h"

class RendererDirectX : public RendererInterface
{
	RendererDirectX* directX;
public:
	RendererDirectX();
	~RendererDirectX();

	HRESULT initD3D(HWND hWndw);
	HRESULT initGeometry(void);
	LRESULT WINAPI msgProc(HWND hWnd, UINT msg, 
		WPARAM wParam, LPARAM lParam);
	int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE,
		LPWSTR, int);

	void cleanUp();
	void setupMatrices();
	void render();
};

#endif