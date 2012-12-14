#ifndef _CUSTOM_VERTEX_FORMATS_H
#define _CUSTOM_VERTEX_FORMATS_H

// We'll still need the Direct3D library for this.
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

// This is a Transformed vertex with a Diffuse colour.
struct Vertex_TD
{
	// fields
	float x, y, z, rhw;
	DWORD colour;

	static const DWORD FORMAT = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
	static const int STRIDE_SIZE = 20;
};

// This is an Untransformed vertex with a Diffuse colour.
struct Vertex_UD 
{
float x, y, z;
DWORD colour;

static const DWORD FORMAT = D3DFVF_XYZ | D3DFVF_DIFFUSE;
static const int STRIDE_SIZE = 16;
};

// This is an Untransformed vertex with a Diffuse colour and Texture.
struct Vertex_UDTx {
float x, y, z;
DWORD colour;
float tu, tv;

static const DWORD FORMAT = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;
static const int STRIDE_SIZE = 24;
};

// This is an Untransformed vertex with a Texture.
struct Vertex_UTx {
float x, y, z;
float tu, tv;

static const DWORD FORMAT = D3DFVF_XYZ | D3DFVF_TEX1;
static const int STRIDE_SIZE = 20;
};

#endif