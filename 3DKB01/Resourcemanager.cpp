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

void Resourcemanager::setDevice(void* argDevice)
{
	device = (LPDIRECT3DDEVICE9)argDevice;
}
void Resourcemanager::loadTexture(std::string argName)
{
	LPCSTR argName_LPCSTR = argName.c_str();
	LPDIRECT3DTEXTURE9 texture;
		
	HRESULT result = D3DXCreateTextureFromFile(device, argName_LPCSTR, &texture);
	Logger::message(result, "D3DXCreateTextureFromFile");
	ResourceTexture* resourceTexture = new ResourceTexture(&texture);
	
	resourceTextures.insert(std::pair<std::string, ResourceTexture*>(argName, resourceTexture));

}

HRESULT Resourcemanager::loadAllMeshes()
{
	//loadMesh();
	return S_OK;
}


HRESULT Resourcemanager::loadMesh(std::string argMeshFile)
{
	LPD3DXBUFFER		pD3DXMtrlBuffer = NULL;
	LPDIRECT3DTEXTURE9*	g_pMeshTextures = NULL;
	LPD3DXMESH			g_pMesh = NULL;
	D3DMATERIAL9*		g_pMeshMaterials = NULL;
	DWORD				g_dwNumMaterials = NULL;
	
	LPCSTR argMeshFile_LPCSTR = argMeshFile.c_str();
	
	if(FAILED(D3DXLoadMeshFromX(argMeshFile_LPCSTR, D3DXMESH_SYSTEMMEM, 
		device, NULL, &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
		&g_pMesh)))
	{
		MessageBox(NULL, "Could not find specified mesh", "Error", MB_OK);
		return E_FAIL;
	}

	ResourceModel* resourceModel = new ResourceModel(g_pMesh);
	resourceModels.insert(std::pair<std::string, ResourceModel*>(argMeshFile, resourceModel));

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

		resourceTextures.insert(std::pair<std::string, ResourceTexture*>(d3dxMaterials[i].pTextureFilename, resourceTexture));

	}
}

ResourceModel*		Resourcemanager::getResourceModel(std::string argString)
{
	std::map<std::string, ResourceModel*>::iterator Iterator;
	for(Iterator = resourceModels.begin(); Iterator != resourceModels.end(); ++Iterator) 
	{
		if (Iterator->first.compare(argString) == 0 )
		{
			return Iterator->second;
		}
	}
}

ResourceTexture*	Resourcemanager::getResourceTexture(std::string argString)
{
	std::map<std::string, ResourceTexture*>::iterator Iterator;
	for(Iterator = resourceTextures.begin(); Iterator != resourceTextures.end(); ++Iterator) 
	{
		if (Iterator->first.compare(argString) == 0 )
		{
			return Iterator->second;
		}
	}
}

std::map<std::string, ResourceModel*> Resourcemanager::getResourceModels()
{
	return resourceModels;
}

std::map<std::string, ResourceTexture*> Resourcemanager::getResourceTextures()
{
	return resourceTextures;
}
