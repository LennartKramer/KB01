#ifndef __RENDERERINTERFACE_H__
#define __RENDERERINTERFACE_H__

#include "CustomVertex.cpp"

#include <d3d9.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>

#pragma warning(disable : 4996)
#pragma warning(default : 4996)

#define D3DFVF_CustomVertex (D3DFVF_XYZ|D3DFVF_DIFFUSE)

interface RendererInterface
{
protected:
	LPDIRECT3D9             g_pD3D;
	LPDIRECT3DDEVICE9       g_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9 g_pVB;
	LPDIRECT3DTEXTURE9		g_pTexture;
};

#endif