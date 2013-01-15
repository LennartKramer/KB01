#ifndef __SCENEHEIGHTMAP_H__
#define __SCENEHEIGHTMAP_H__

#include <fstream>
#include <iostream>
#include <d3d9.h>
#include <d3dx9math.h>

class SceneHeightmap
{
private:
	int bmpOffset;
	int bmpWidth;
	int bmpHeight;
public:
	SceneHeightmap(void);
	~SceneHeightmap(void);

	bool initializeDimensions(LPCSTR fileName);
	
	int getBitmapOffset(void);
	int getBitmapHeight(void);
	int getBitmapWidth(void);

	int set_offset (void);
	long set_height (void);
	long set_width (void);

	
};

#endif