#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <d3dx9.h>
#include <d3d9.h>
#include <strsafe.h>
#include <mmsystem.h>
#include <fstream>

class Resourcemanager
{
private:
	LPD3DXBUFFER		pD3DXMtrlBuffer;

	LPD3DXMESH          g_pMesh;
	D3DMATERIAL9*       g_pMeshMaterials;
	LPDIRECT3DTEXTURE9* g_pMeshTextures;
	DWORD               g_dwNumMaterials;

	int imageDimensions;
public:
	Resourcemanager(void);
	~Resourcemanager(void);

	LPD3DXMESH getMesh(void);
	D3DMATERIAL9* getMeshMaterials(void);
	LPDIRECT3DTEXTURE9* getMeshTextures(void);
	DWORD getDwNumMaterials(void);

	HRESULT loadMaterials(LPDIRECT3DDEVICE9 device);
};

#endif __RESOURCEMANAGER_H__