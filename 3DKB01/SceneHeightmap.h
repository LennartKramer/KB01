#ifndef __SCENEHEIGHTMAP_H__
#define __SCENEHEIGHTMAP_H__

#include <iostream>
#include <d3d9.h>
#include <d3dx9math.h>

#include <d3d11.h>
#include <d3dx10math.h>
#include <stdio.h>

class SceneHeightmap
{

private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};

public:
	SceneHeightmap(void);
	SceneHeightmap(const SceneHeightmap&);
	~SceneHeightmap(void);

	bool Initialize(ID3D11Device*, char*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

private:
	bool LoadHeightMap(char*);
	void NormalizeHeightMap();
	void ShutdownHeightMap();

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	
	int m_terrainWidth, m_terrainHeight;
	int m_vertexCount, m_indexCount;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;

private:
	HeightMapType* m_heightMap;
};

#endif