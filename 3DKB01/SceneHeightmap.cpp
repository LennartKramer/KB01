#include "SceneHeightmap.h"
#include <iostream>

SceneHeightmap::SceneHeightmap(void)
{

};


SceneHeightmap::~SceneHeightmap(void)
{

};

bool SceneHeightmap::initializeDimensions(const char * fileName, HWND hWnd)
{
	return true;
};

void SceneHeightmap::divideHeightMap(void)
{
	int i, j;

	for(j = 0; j < bmpHeight; j++)
	{
		for(i = 0; i < bmpWidth; i++)
		{
			heightMap_struct[(bmpHeight * j) + i].y /= 15.0f;
		}
	}
};

void SceneHeightmap::shutdownHeightMap(void)
{
	if(heightMap_struct)
	{
		delete [] heightMap_struct;
		heightMap_struct = 0;
	}
};

int SceneHeightmap::getBitmapWidth(void)
{
	return bmpWidth;
};

int SceneHeightmap::getBitmapHeight(void)
{
	return bmpHeight;
};

HeightMapType* SceneHeightmap::getHeightMapData(void)
{
	return heightMap_struct;
};
