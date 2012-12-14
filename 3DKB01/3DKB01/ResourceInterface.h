#ifndef _RESOURCEINTERFACE_H
#define _RESOURCEINTERFACE_H

#include <d3dx9.h>
#include <d3d9.h>
#include <iostream>

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")

class ResourceInterface
{
public:
	ResourceInterface(void);
	~ResourceInterface(void);

	virtual void loadTextures(void);
	virtual void loadModels(void);
	virtual LPD3DXBUFFER getLPD3DXBUFFER(void);
protected:
	LPDIRECT3D9         g_pD3D;
	LPDIRECT3DDEVICE9   g_pd3dDevice;
	LPD3DXBUFFER		pD3DXMtrlBuffer;

	LPD3DXMESH          g_pMesh;
	D3DMATERIAL9*       g_pMeshMaterials;
	LPDIRECT3DTEXTURE9* g_pMeshTextures;
	DWORD               g_dwNumMaterials;
};

#endif _RESOURCEINTERFACE_H