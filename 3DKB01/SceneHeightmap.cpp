#include "SceneHeightmap.h"
#include <iostream>
#include <string>

SceneHeightmap::SceneHeightmap(void)
{

};


SceneHeightmap::~SceneHeightmap(void)
{

};

bool SceneHeightmap::initializeDimensions(LPCTSTR fileName, HWND hWnd)
{
	BITMAP bmp;

	HDC lhdcDest = NULL;
	HBITMAP phBitmap = NULL;
	HPALETTE *phPalette = NULL;
	HINSTANCE hInst = NULL;
	//HANDLE test;

	phBitmap = (HBITMAP)LoadImageA(hInst, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	// std::string fileNameTest = "C:\\Users\\Peter-Pim\\Documents\\Opleiding Informatica\\Informatica Cursus 2012 en 2013\\Blok 6 (3D - Engine)\\Project\\Applicatie\\3DKB01\\heightmap.bmp";
	// const char* c = fileNameTest.c_str();
	// test = LoadImage(hInst, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// DWORD error = GetLastError();

	if(phBitmap == NULL)
	{
		MessageBox(hWnd, "SceneHeightmap initializeDimensions: Could not find bitmap file", "Error", MB_OK);
		return false;
	}

	SelectObject(lhdcDest, phBitmap);

	GetObject(phBitmap, sizeof(BITMAP), (void*)&bmp);

	bmpWidth = bmp.bmWidth;
	bmpHeight = bmp.bmHeight;

	heightMap_struct = new HeightMapType[bmpWidth * bmpHeight];
	if(!heightMap_struct)
	{
		MessageBox(hWnd, "SceneHeightmap initializeDimensions: Could not build HeightMapType struct", "Error", MB_OK);
		return false;
	}

	k = 0;

	for(j = 0; j < bmpHeight; j++)
	{
		for(i = 0; i < bmpWidth; i++)
		{
			height = bmpImage[k];

			index = (bmpHeight * j) + i;

			heightMap_struct[index].x = (float)i;
			heightMap_struct[index].y = (float)height;
			heightMap_struct[index].z = (float)j;

			k += 3;
		}
	}
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
