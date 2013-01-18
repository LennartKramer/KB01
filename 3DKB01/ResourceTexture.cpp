#include "ResourceTexture.h"


ResourceTexture::ResourceTexture(LPDIRECT3DTEXTURE9* argTexture)
{
	g_pMeshTextures = *argTexture;
}

ResourceTexture::~ResourceTexture()
{
}

LPDIRECT3DTEXTURE9 ResourceTexture::getMeshTextures()
{
	return g_pMeshTextures;
}