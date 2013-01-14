#ifndef __SCENEHEIGHTMAP_H__
#define __SCENEHEIGHTMAP_H__

#include <fstream>
#include <iostream>
#include <d3d9.h>
#include <d3dx9math.h>

#include "HeightMapStructs.h"

class SceneHeightmap
{
private:
	HeightMapType* heightMap_struct;

	int bmpWidth;
	int bmpHeight;
	int imageSize;
	int i, j, k, index;
	unsigned char *bmpImage;
	unsigned char height;

	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
public:
	SceneHeightmap(void);
	~SceneHeightmap(void);

	void divideHeightMap(void);
	void shutdownHeightMap(void);

	bool initializeDimensions(LPCTSTR fileName, HWND hWnd);
	int getBitmapWidth(void);
	int getBitmapHeight(void);
	HeightMapType* getHeightMapData(void);
	
};

#endif