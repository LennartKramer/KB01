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

	void initD3D(HWND hWndw);

	void cleanUp(void);

	void setupWorldMatrix();
	void setupViewMatrix(Vector pvEyePt, Vector pvLookatPt); 
	void setupProjectionMatrix(FLOAT fFOV, FLOAT fAspect, FLOAT fNearPlane, FLOAT fFarPlane);
	void updateCamera(Vector* pvEyePt, Vector* pvLookatPt,float cameraYaw, float cameraPitch);

	void createVertexBuffer(int, std::string, CUSTOMVERTEX*);
	void createIndexBuffer(int, const std::string&, short*);

	void beginScene(void);
	void endScene(void);
	void clear(void);
	void present(HWND hWnd);
	void setFvf(void);
	void zBufferEnable(void);
	void zBufferDisable(void);

	void setTexture(ResourceTexture*);
	void moveMatrix(Vector argOrientation, Vector argPosition);

	void drawPrimitive(void);
	void drawIndexedPrimitive(int, int);

	void setStreamSource(std::string);
	void setIndices(std::string);

	void* getDevice();
private:
	std::map<std::string, LPDIRECT3DVERTEXBUFFER9>	vertexBufferMap;
	std::map<std::string, LPDIRECT3DINDEXBUFFER9>	indexBufferMap;
	std::map<std::string, LPDIRECT3DSWAPCHAIN9>		swapChainMap;

	LPDIRECT3D9             g_pD3D;
	LPDIRECT3DDEVICE9       g_pd3dDevice;
	D3DXMATRIX				m_mView;
	D3DXMATRIX				m_mProj;
};

#endif