#ifndef __ResourceTexture_H__
#define __ResourceTexture_H__

#include <d3dx9.h>
#include <d3d9.h>

class ResourceTexture
{
private:
	LPDIRECT3DTEXTURE9 g_pMeshTextures;
public:
	ResourceTexture(LPDIRECT3DTEXTURE9*);
	~ResourceTexture();
	LPDIRECT3DTEXTURE9 getMeshTextures();
};

#endif