#ifndef __SCENEHEIGHTMAP_H__
#define __SCENEHEIGHTMAP_H__

#include <fstream>
#include <iostream>
#include <d3d9.h>
#include <d3dx9math.h>

class SceneHeightmap
{
private:
	unsigned int bmpOffset;
	unsigned int bmpWidth;
	unsigned int bmpHeight;
public:
	SceneHeightmap(void);
	~SceneHeightmap(void);

	bool initializeDimensions(LPCSTR fileName);
	int getBitmapOffset(void);
	int getBitmapWidth(void);
	int getBitmapHeight(void);
};

#endif