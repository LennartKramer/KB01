#ifndef __RENDERERINTERFACE_H__
#define __RENDERERINTERFACE_H__

#include "CustomVertex.h"

#include <d3d9.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>
#include <fstream>

#pragma warning(disable : 4996)
#pragma warning(default : 4996)

#define D3DFVF_CustomVertex (D3DFVF_XYZ|D3DFVF_DIFFUSE)

interface RendererInterface
{
public:
	RendererInterface(void);
	~RendererInterface(void);
};

#endif