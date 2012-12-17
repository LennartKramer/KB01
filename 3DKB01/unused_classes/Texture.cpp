#include "Texture.h"

Texture::Texture(void)
{
	// Constructor. Leave empty for now
};

Texture::~Texture(void)
{
	// Destructor. Leave empty for now
};

void Texture::loadModels(void)
{
	// This class has nothing to do with Models.
};

void Texture::loadTextures(void)
{
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
	if(g_pMeshTextures == NULL)
	{
		throw (TEXT("Out of Memory! Could not create Texture."));
		return;
	}
	for(DWORD i = 0; i < g_dwNumMaterials; i++)
	{
		g_pMeshTextures[i] = NULL;
		if(d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
		{
			// Build the texture.
			if(FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, d3dxMaterials[i].pTextureFilename,
				&g_pMeshTextures[i])))
			{
				throw (TEXT("Could not find texture map."));
				return;
			} else
				d3dxMaterials[i].pTextureFilename = "textures";
			if(FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, d3dxMaterials[i].pTextureFilename,
				&g_pMeshTextures[i])))
			{
				throw (TEXT("Could not find texture in specified folder:")); 
				std::cout << d3dxMaterials[i].pTextureFilename;
				return;
			}
		}
	}
};

LPD3DXBUFFER Texture::getLPD3DXBUFFER(void)
{
	return pD3DXMtrlBuffer;
};
