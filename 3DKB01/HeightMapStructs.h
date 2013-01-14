#ifndef _HEIGHTMAPSTRUCT_H
#define _HEIGHTMAPSTRUCT_H

#include <d3d9.h>
#include <d3dx9math.h>

struct VertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR4 color;
};

struct HeightMapType
{
	float x, y, z;
};

#endif _HEIGHTMAPSTRUCT_H