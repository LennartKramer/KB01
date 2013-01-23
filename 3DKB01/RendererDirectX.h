#ifndef __RENDERERDIRECTX_H__
#define __RENDERERDIRECTX_H__

#include "RendererInterface.h"
#include <d3d9.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>
#include <map>
#include <iostream>
#include <string>

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_TEX1)

class RendererDirectX : public RendererInterface
{
public:
	RendererDirectX(void);
	~RendererDirectX(void);

	HRESULT initD3D(HWND hWndw);

	void cleanUp(void);
	void setupCamera(const D3DXVECTOR3* eyePT, const D3DXVECTOR3*Lookat);
	void setupWorldMatrix(Vector, Vector);

	void createVertexBuffer(int, std::string, CUSTOMVERTEX*);
	void createIndexBuffer(int, const std::string&, short*);

	void beginScene(void);
	void endScene(void);
	void clear(void);
	void present(void);
	void setFvf(std::string);
	void zBufferEnable() { g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE); }
	void zBufferDisable() { g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE); }

	void setTexture(ResourceTexture*);

	void drawPrimitive();
	void drawIndexedPrimitive(float, float, float, int, int);

	void setStreamSource(std::string);
	void setIndices(std::string);

	LPDIRECT3DDEVICE9 getDevice();
	LPDIRECT3DSWAPCHAIN9 getSwapChain(std::string);

	
private:
	std::map<std::string, LPDIRECT3DVERTEXBUFFER9>	vertexBufferMap;
	std::map<std::string, LPDIRECT3DINDEXBUFFER9>	indexBufferMap;
	std::map<std::string, LPDIRECT3DSWAPCHAIN9>		swapChainMap;

	LPDIRECT3D9             g_pD3D;
	LPDIRECT3DDEVICE9       g_pd3dDevice;

//	LPDIRECT3DTEXTURE9		g_pTexture;
//	Vertex_TD*				vertex_Vertices;
};

#endif