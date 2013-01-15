#ifndef __RENDERERDIRECTX_H__
#define __RENDERERDIRECTX_H__

#include "RendererInterface.h"
#include <d3d9.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>

#include <iostream>

class RendererDirectX : public RendererInterface
{
public:
	RendererDirectX(void);
	~RendererDirectX(void);

	HRESULT initD3D(HWND hWndw);

	void cleanUp(void);
	void setupCamera(Vector, Vector, Vector);
	void setupWorldMatrix(Vector, Vector);

	void beginScene(void);
	void endScene(void);
	void clear(void);
	void present(void);
	void setFvf(void);

	void setTexture(ResourceTexture*);

	void fillVertices(int, int, int);
	void fillIndices(int, int, int);

	void drawPrimitive(float, float, int, int);

	void setStreamSource(void);
	void setIndices(void);

	// void render(void* g_pMeshTextures, void* g_pMesh, int bmpWidth, int bmpHeight);

	void* getDevice(void);

//	void initializeVertices(HWND hWnd, void* g_pd3dDevice, int bmpOffset, int bmpWidth, int bmpHeight);
//	void initializeIndices(HWND hWnd, void* g_pd3dDevice, int bmpWidth, int bmpHeight);
	//LPDIRECT3DDEVICE9
private:
	LPDIRECT3D9             g_pD3D;
	LPDIRECT3DDEVICE9       g_pd3dDevice;
	LPDIRECT3DINDEXBUFFER9  g_pIB;
	LPDIRECT3DVERTEXBUFFER9 g_pVB;
	LPDIRECT3DTEXTURE9		g_pTexture;

	Vertex_TD *vertex_Vertices;
};

#endif