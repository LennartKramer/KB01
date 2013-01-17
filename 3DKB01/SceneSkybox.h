#ifndef __SCENESKYBOX_H__
#define __SCENESKYBOX_H__

#include "RendererInterface.h"
#include <d3d9.h>
#include <strsafe.h>
#include <string>

class SceneSkybox
{

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_TEX1)

public:

	SceneSkybox();
	SceneSkybox(RendererInterface*, ResourceTexture*);
	~SceneSkybox(void);
	void initialize();
	HRESULT initVB();
	ResourceTexture* getTexture() { return texture; }
	void Render();
private:
	RendererInterface*		renderer;	
	ResourceTexture*		texture;
};


#endif