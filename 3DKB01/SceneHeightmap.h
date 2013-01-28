#ifndef __SCENEHEIGHTMAP_H__
#define __SCENEHEIGHTMAP_H__

#include <fstream>
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

	void fillVertices(LPCSTR);
	void fillIndices();

	void render();

	void initializeDimensions(LPCSTR);
	
	int getBitmapOffset(void);
	int getBitmapHeight(void);
	int getBitmapWidth(void);

	int set_offset (LPCSTR);
	long set_height (LPCSTR);
	long set_width (LPCSTR);

	void setPosition(Vector);
	Vector getPosition();

	void setOrientation(Vector);
	Vector getOrientation();
};

#endif