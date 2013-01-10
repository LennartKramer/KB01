#ifndef __SCENESKYBOX_H__
#define __SCENESKYBOX_H__

#include <d3d9.h>
#include <strsafe.h>
#include "RendererDirectX.h"
#include <string>

class SceneSkybox
{
public:

	SceneSkybox();
	SceneSkybox(RendererDirectX*);
	~SceneSkybox(void);
	void initialize();
	HRESULT InitVB();
	void Render();

	RendererDirectX* directX;
	LPDIRECT3D9             g_pD3D; // Used to create the D3DDevice
	LPDIRECT3DVERTEXBUFFER9 g_pVB; // Buffer to hold vertices

	// A structure for our custom vertex type
	struct CUSTOMVERTEX
	{
		FLOAT x, y, z; // The transformed position for the vertex
		DWORD color;        // The vertex color
	};

	// Our custom FVF, which describes our custom vertex structure
	#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

};


#endif