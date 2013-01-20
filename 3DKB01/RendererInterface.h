#ifndef __RENDERERINTERFACE_H__
#define __RENDERERINTERFACE_H__

#include "ResourceTexture.h"
#include "VECTOR.h"
#include <fstream>

#pragma warning(disable : 4996)
#pragma warning(default : 4996)

struct CUSTOMVERTEX
{
//	CUSTOMVERTEX(){}
//	CUSTOMVERTEX(float argX,float argY,float argZ,float argFU,float argFV){ x = argX; y = argY; z = argZ; fU = argFU; fV = argFV; }

	float x,y,z;
	float fU, fV;
};

interface RendererInterface
{
public:
	RendererInterface(void){}
	~RendererInterface(void){}

	virtual HRESULT initD3D(HWND hWnd) = 0;
	virtual void cleanUp(void){}
	
	virtual void setupCamera(const D3DXVECTOR3* eyePT, const D3DXVECTOR3*Lookat){}	
	virtual void setupWorldMatrix(Vector, Vector){}

	virtual void* getDevice(void) = 0;
	
	virtual void createVertexBuffer(int, std::string, CUSTOMVERTEX*){}
	virtual void createIndexBuffer(int, const std::string&, short*) = 0;


	virtual void clear(void){}
	virtual void beginScene(void){}
	virtual void endScene(void){}
	virtual void present(void){}
	virtual void setFvf(std::string){}

	virtual void setTexture(ResourceTexture*){}

	virtual void drawPrimitive(){}
	virtual void drawIndexedPrimitive(float, float, float, int, int){}

	virtual void setStreamSource(std::string){}
	virtual void setIndices(std::string){}

	virtual void initializeVertices(HWND hWnd, void* g_pd3dDevice,
		int bmpOffset, int bmpWidth, int bmpHeight){}

	virtual void initializeIndices(HWND hWnd, void* g_pd3dDevice,
		int bmpWidth, int bmpHeight){}

};

#endif