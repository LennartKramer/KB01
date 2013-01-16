#include "SceneSkybox.h"



SceneSkybox::SceneSkybox()
{
	initialize();
}


SceneSkybox::SceneSkybox(RendererInterface* argRendererDirectX)
{
	directX = argRendererDirectX;
	initialize();
}


SceneSkybox::~SceneSkybox(void)
{
}



void SceneSkybox::initialize()
{
	g_pD3D = NULL; 
	texture = NULL;

	directX->createSkybox();
}


// Does the rendering of the skybox.
void SceneSkybox::Render()
{
	LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9) directX->getDevice();

	//load texture from file
	D3DXCreateTextureFromFile(device, "textures/skybox.png", &texture);

	ResourceTexture* skybox = new ResourceTexture(&texture);
	
	//set texture
	directX->setTexture(skybox);
	
    // Draw the triangles in the vertex buffer. 
	// We are passing the vertices down a "stream".
	// We let the D3D know what vertex shader to use.
	// We call the DrawPrimitive which does the renderering.

	directX->setStreamSource();
	directX->setFvf();
	directX->drawPrimitive();
}

