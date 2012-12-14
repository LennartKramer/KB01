#include "Model.h"

Model::Model(void)
{
	// Constructor. Leave empty for now
};

Model::~Model(void)
{
	// Destructor. Leave empty for now
};

void Model::loadModels(void)
{
	if(FAILED(D3DXLoadMeshFromX("meshes/Tiger.x", D3DXMESH_SYSTEMMEM,
		g_pd3dDevice, NULL, &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials, 
		&g_pMesh)))
	{
		throw (TEXT("Could not find concerning model."));
		return;
	}
	// Extract material properties from the pD3DXMtrlBuffer.
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
	if(g_pMeshMaterials == NULL)
	{
		throw (TEXT("Out of Memory! Could not create mesh."));
		return;
	}
	for(DWORD i = 0; i < g_dwNumMaterials; i++)
	{
		// Copy the materials
		g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		// Set the ambient color for all the materials.
		g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;
	}
	// Ending of the Model loader method.
};

void Model::loadTextures(void)
{
	// This class has nothing to do with Textures.
};

LPD3DXBUFFER Model::getLPD3DXBUFFER(void)
{
	return pD3DXMtrlBuffer;
};