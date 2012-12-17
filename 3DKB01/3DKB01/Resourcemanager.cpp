#include "Resourcemanager.h"


Resourcemanager::Resourcemanager(void)
{
	g_pD3D = 0;
	g_pd3dDevice = 0;
	pD3DXMtrlBuffer = 0;
	
	g_pMesh = 0;
	g_pMeshMaterials = 0;
	g_pMeshTextures = 0;
	g_dwNumMaterials = 0L;
};

Resourcemanager::~Resourcemanager(void)
{
	// Destructor. Leave this empty for now.
};

/*
/ Load the models and textures from specified files.
/ Then extract the material properties and texture names
/ from the pD3DXMtrlBuffer. Copy the material and then create
/ the texture. As last add the model to a list, so they can 
/ be retrieved at any time.
*/
HRESULT Resourcemanager::loadMaterials(void)
{
	LPD3DXBUFFER pD3DXMtrlBuffer;

	LPCTSTR meshFile = TEXT("meshes/tiger.x");
	if(FAILED(D3DXLoadMeshFromX("meshes/tiger.x", D3DXMESH_SYSTEMMEM,
		g_pd3dDevice, NULL, &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
		&g_pMesh)))
	{
		MessageBox(NULL, "Could not find specified meshes map.", "Meshes.exe", MB_OK);
		return E_FAIL;
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*) pD3DXMtrlBuffer->GetBufferPointer();
	g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
	if(g_pMeshMaterials == NULL)
		return E_OUTOFMEMORY;
	g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
	if( g_pMeshTextures == NULL )
        return E_OUTOFMEMORY;
	for(DWORD i = 0; i < g_dwNumMaterials; i++)
	{
		g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;
		g_pMeshTextures[i] = NULL;
		d3dxMaterials[i].pTextureFilename = "textures";
		if(d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if(FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice,
				d3dxMaterials[i].pTextureFilename, &g_pMeshTextures[i])))
			{
				MessageBox(NULL, "Could not find specified texture map.", "Textures.exe", MB_OK);
			}
		}
	}
	// Release material buffer since we don't need it anymore.
	pD3DXMtrlBuffer->Release();

	return S_OK;
};
