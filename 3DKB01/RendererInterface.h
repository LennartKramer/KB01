#ifndef __RENDERERINTERFACE_H__
#define __RENDERERINTERFACE_H__

#include "ResourceTexture.h"
#include "VECTOR.h"
#include <fstream>

#pragma warning(disable : 4996)
#pragma warning(default : 4996)

struct CUSTOMVERTEX
{
	float x,y,z;
	float fU, fV;
};

interface RendererInterface
{
public:
	RendererInterface(void){}
	~RendererInterface(void){}

	virtual HRESULT initD3D(HWND hWnd) = 0;
	virtual void cleanUp(void)=0;
	
	virtual void setupCamera(const D3DXVECTOR3* eyePT, const D3DXVECTOR3*Lookat)=0;	

	virtual LPDIRECT3DDEVICE9 getDevice() = 0;
	virtual LPDIRECT3DSWAPCHAIN9 getSwapChain(std::string) = 0;
	
	virtual void createVertexBuffer(int, std::string, CUSTOMVERTEX*)=0;
	virtual void createIndexBuffer(int, const std::string&, short*) = 0;


	virtual void clear(void)=0;
	virtual void beginScene(void)=0;
	virtual void endScene(void)=0;
	virtual void present(void)=0;
	virtual void setFvf(void)=0;
	virtual void zBufferEnable(void)=0;
	virtual void zBufferDisable(void)=0;

	virtual void setupWorldMatrix()=0;
	virtual void moveMatrix(Vector argOrientation, Vector argPosition)=0;
	virtual void setTexture(ResourceTexture*)=0;

	virtual void drawPrimitive()=0;
	virtual void drawIndexedPrimitive(int, int)=0;

	virtual void setStreamSource(std::string)=0;
	virtual void setIndices(std::string)=0;
};

#endif