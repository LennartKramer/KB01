#ifndef __SCENEHEIGHTMAP_H__
#define __SCENEHEIGHTMAP_H__

#include <fstream>
#include <iostream>
#include <d3d9.h>
#include <d3dx9math.h>

#include "RendererInterface.h"

class SceneHeightmap
{
private:
	int bmpOffset;
	int bmpWidth;
	int bmpHeight;

	Vector position;
	Vector orientation;

	RendererInterface* renderer;
	ResourceTexture* texture;
public:
	SceneHeightmap(void);
	SceneHeightmap(RendererInterface*, std::string, ResourceTexture*);
	~SceneHeightmap(void);

	void fillVertices();
	void fillIndices();

	void render();

	bool initializeDimensions(LPCSTR fileName);
	
	int getBitmapOffset(void);
	int getBitmapHeight(void);
	int getBitmapWidth(void);

	int set_offset (void);
	long set_height (void);
	long set_width (void);

	void setPosition(Vector argPosition){position = argPosition;}
	Vector getPosition(){return position;}

	void setOrientation(Vector argOrientation){orientation = argOrientation;}
	Vector getOrientation(){return orientation;}


};

#endif