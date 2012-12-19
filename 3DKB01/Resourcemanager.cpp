#include "Resourcemanager.h"
#include <iostream>

Resourcemanager::Resourcemanager()
{
};

Resourcemanager::~Resourcemanager(void)
{
	// Destructor. Leave this empty for now.
};

/*
	LoadAllMeshes will be used at initialization and use the loadmesh method
*/

void Resourcemanager::setDevice(LPDIRECT3DDEVICE9 argDevice)
{
	device = argDevice;
}

	

HRESULT Resourcemanager::loadAllMeshes()
{
	//loadMesh();
	return S_OK;
}


HRESULT Resourcemanager::loadMesh(LPCTSTR argMeshFile)
{
	LPD3DXBUFFER		pD3DXMtrlBuffer = NULL;
	LPDIRECT3DTEXTURE9*	g_pMeshTextures = NULL;
	LPD3DXMESH			g_pMesh = NULL;
	D3DMATERIAL9*		g_pMeshMaterials = NULL;
	DWORD				g_dwNumMaterials = NULL;

	if(FAILED(D3DXLoadMeshFromX(argMeshFile, D3DXMESH_SYSTEMMEM, 
		device, NULL, &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
		&g_pMesh)))
	{
		MessageBox(NULL, "Could not find specified mesh", "Error", MB_OK);
		return E_FAIL;
	}

	ResourceModel* resourceModel = new ResourceModel(&g_pMesh);
	resourceModels.insert(std::pair<LPCTSTR, ResourceModel*>(argMeshFile, resourceModel));

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*) pD3DXMtrlBuffer->GetBufferPointer();
	g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
	g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];

	
	for(DWORD i = 0; i < g_dwNumMaterials; i++)
	{
		g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
	 	g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;
		g_pMeshTextures[i] = NULL;
		if(d3dxMaterials[i].pTextureFilename != NULL)
		{	
				D3DXCreateTextureFromFileA(device, d3dxMaterials[i].pTextureFilename, &g_pMeshTextures[i]);	
		}

		ResourceTexture* resourceTexture = new ResourceTexture(&g_pMeshTextures[i]);

		resourceTextures.insert(std::pair<LPCTSTR, ResourceTexture*>(d3dxMaterials[i].pTextureFilename, resourceTexture));

	}
}

ResourceModel*		Resourcemanager::getResourceModel(LPCTSTR argString)
{
	std::map<LPCTSTR, ResourceModel*>::iterator Iterator;
	for(Iterator = resourceModels.begin(); Iterator != resourceModels.end(); ++Iterator) 
	{
		if (Iterator->first == argString)
		{
			return Iterator->second;
		}
	}
}

ResourceTexture*	Resourcemanager::getResourceTexture(LPCTSTR argString)
{
	std::map<LPCTSTR, ResourceTexture*>::iterator Iterator;
	for(Iterator = resourceTextures.begin(); Iterator != resourceTextures.end(); ++Iterator) 
	{
		std::cout << argString << std::endl;
		
		std::cout << Iterator->first;

		if (Iterator->first == argString)
		{
			std::cout << Iterator->second;
			return Iterator->second;
		}
	}
}


/*
/ HRESULT LoadMaterials(void);
/ Load the models and textures from specified files.
/ Then extract the material properties and texture names
/ from the pD3DXMtrlBuffer. Copy the material and then create
/ the texture. As last add the model to a list, so they can 
/ be retrieved at any time.
*/

/*
HRESULT Resourcemanager::loadMaterials(LPDIRECT3DDEVICE9 device)
{
	LPD3DXBUFFER pD3DXMtrlBuffer;
	LPCTSTR meshFile = TEXT("meshes/tiger.x");
	
	
	if(FAILED(D3DXLoadMeshFromX("meshes/tiger.x", D3DXMESH_SYSTEMMEM, 
		device, NULL, &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
		&g_pMesh)))
	{
		MessageBox(NULL, "Could not find specified mesh", "Error", MB_OK);
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
		if(d3dxMaterials[i].pTextureFilename != NULL && lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if(FAILED(D3DXCreateTextureFromFileA(device,
				d3dxMaterials[i].pTextureFilename, &g_pMeshTextures[i])))
			{
				MessageBox(NULL, "Could not find specified texture", "Error", MB_OK);
			}
		}
	}

	// Release material buffer since we don't need it anymore.
	pD3DXMtrlBuffer->Release();

	return S_OK;
};
*/