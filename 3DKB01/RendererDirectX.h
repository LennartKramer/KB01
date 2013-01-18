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
	void setupCamera(Vector, Vector, Vector);
	void setupWorldMatrix(Vector, Vector);

	void createVertexBuffer(int, std::string, CUSTOMVERTEX*);
	void createIndexBuffer(int, const std::string&, short*);

	void beginScene(void);
	void endScene(void);
	void clear(void);
	void present(void);
	void setFvf(std::string);

	void setTexture(ResourceTexture*);

	void drawPrimitive();
	void drawIndexedPrimitive(float, float, float, int, int);

	void setStreamSource(std::string);
	void setIndices(std::string);

	void* getDevice(void);


	
private:
	std::map<std::string, LPDIRECT3DVERTEXBUFFER9>	vertexBufferMap;
	std::map<std::string, LPDIRECT3DINDEXBUFFER9>	indexBufferMap;

	LPDIRECT3D9             g_pD3D;
	LPDIRECT3DDEVICE9       g_pd3dDevice;

//	LPDIRECT3DTEXTURE9		g_pTexture;
//	Vertex_TD*				vertex_Vertices;
};

#endif