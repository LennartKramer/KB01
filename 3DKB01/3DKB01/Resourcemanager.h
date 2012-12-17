#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <d3dx9.h>
#include <d3d9.h>
#include <strsafe.h>
#include <mmsystem.h>
#include <iostream>

class Resourcemanager
{
private:
	LPDIRECT3D9         g_pD3D;
	LPDIRECT3DDEVICE9   g_pd3dDevice;
	LPD3DXBUFFER		pD3DXMtrlBuffer;

	LPD3DXMESH          g_pMesh;
	D3DMATERIAL9*       g_pMeshMaterials;
	LPDIRECT3DTEXTURE9* g_pMeshTextures;
	DWORD               g_dwNumMaterials;
public:
	Resourcemanager(void);
	~Resourcemanager(void);

	HRESULT loadMaterials(void);
};

#endif __RESOURCEMANAGER_H__