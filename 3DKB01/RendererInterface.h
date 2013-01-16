#ifndef __RENDERERINTERFACE_H__
#define __RENDERERINTERFACE_H__

#include "ResourceTexture.h"
#include "CustomVertex.h"
#include "VECTOR.h"
#include <fstream>

#pragma warning(disable : 4996)
#pragma warning(default : 4996)

#define D3DFVF_CustomVertex (D3DFVF_XYZ|D3DFVF_DIFFUSE)

interface RendererInterface
{
public:
	RendererInterface(void){}
	~RendererInterface(void){}

	virtual HRESULT initD3D(HWND hWnd) = 0;
	virtual void cleanUp(void){}
	
	virtual void setupCamera(Vector, Vector ,Vector){}	
	virtual void setupWorldMatrix(Vector, Vector){}

	virtual void* getDevice(void) = 0;
	
	virtual void clear(void){}
	virtual void beginScene(void){}
	virtual void endScene(void){}
	virtual void present(void){}
	virtual void setFvf(void){}

	virtual void setTexture(ResourceTexture*){}

	virtual HRESULT createSkybox() = 0;

	virtual void fillVertices(int, int, int){}
	virtual void fillIndices(int, int, int){}


	virtual void drawPrimitive(){}
	virtual void drawIndexedPrimitive(float, float, float, int, int){}

	virtual void setStreamSource(void){}
	virtual void setIndices(void){}

	virtual void initializeVertices(HWND hWnd, void* g_pd3dDevice,
		int bmpOffset, int bmpWidth, int bmpHeight){}

	virtual void initializeIndices(HWND hWnd, void* g_pd3dDevice,
		int bmpWidth, int bmpHeight){}

};

#endif