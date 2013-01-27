#include "SceneSkybox.h"
#include "Resourcemanager.h"


SceneSkybox::SceneSkybox()
{
	initVB();
}


SceneSkybox::SceneSkybox(RendererInterface* argRendererDirectX, ResourceTexture* argTexture)
{
	renderer = argRendererDirectX;
	texture = argTexture;
	initVB();
}


SceneSkybox::~SceneSkybox(void)
{
}

HRESULT SceneSkybox::initVB()
{
	float size = 10.0f;
	
	CUSTOMVERTEX vertices[] =
    {
       	//bottom
		{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
<<<<<<< .mine
		{ 0.0f, 0.0f, 100.0f, 0.0f, 0.0f },
		{ 100.0f, 0.0f, 100.0f, 0.0f, 0.0f },
=======
		{ 0.0f, 0.0f, size, 0.0f, 0.0f },
		{ size, 0.0f, size, 0.0f, 0.0f },
>>>>>>> .r72

		{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
<<<<<<< .mine
		{ 100.0f, 0.0f, 100.0f, 0.0f, 0.0f },
		{ 100.0f, 0.0f, 0.0f, 0.0f, 0.0f },
=======
		{ size, 0.0f, size, 0.0f, 0.0f },
		{ size, 0.0f, 0.0f, 0.0f, 0.0f },
>>>>>>> .r72


		//back
<<<<<<< .mine
		{ 0.0f, 0.0f, 100.0f, 0.2f, 1.0f },
		{ 0.0f, 100.0f, 100.0f, 0.2f, 0.0f },
		{ 100.0f, 100.0f, 100.0f, 0.4f, 0.0f },
=======
		{ 0.0f, 0.0f, size, 0.2f, 1.0f },
		{ 0.0f, size, size, 0.2f, 0.0f },
		{ size, size, size, 0.4f, 0.0f },
>>>>>>> .r72

<<<<<<< .mine
		{ 0.0f, 0.0f, 100.0f, 0.2f, 1.0f },
		{ 100.0f, 0.0f, 100.0f, 0.4f, 1.0f },
		{ 100.0f, 100.0f, 100.0f, 0.4f, 0.0f },
=======
		{ 0.0f, 0.0f, size, 0.2f, 1.0f },
		{ size, 0.0f, size, 0.4f, 1.0f },
		{ size, size, size, 0.4f, 0.0f },
>>>>>>> .r72


		//right
<<<<<<< .mine
		{ 100.0f, 0.0f, 0.0f, 0.6f, 1.0f },
		{ 100.0f, 100.0f, 0.0f, 0.6f, 0.0f },
		{ 100.0f, 100.0f, 100.0f, 0.4f, 0.0f },
=======
		{ size, 0.0f, 0.0f, 0.6f, 1.0f },
		{ size, size, 0.0f, 0.6f, 0.0f },
		{ size, size, size, 0.4f, 0.0f },
>>>>>>> .r72

<<<<<<< .mine
		{ 100.0f, 0.0f, 0.0f, 0.6f, 1.0f },
		{ 100.0f, 0.0f, 100.0f, 0.4f, 1.0f },
		{ 100.0f, 100.0f, 100.0f, 0.4f, 0.0f },
=======
		{ size, 0.0f, 0.0f, 0.6f, 1.0f },
		{ size, 0.0f, size, 0.4f, 1.0f },
		{ size, size, size, 0.4f, 0.0f },
>>>>>>> .r72


		//left
		{ 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
<<<<<<< .mine
		{ 0.0f, 0.0f, 100.0f, 0.2f, 1.0f },
		{ 0.0f, 100.0f, 100.0f, 0.2f, 0.0f },
=======
		{ 0.0f, 0.0f, size, 0.2f, 1.0f },
		{ 0.0f, size, size, 0.2f, 0.0f },
>>>>>>> .r72

		{ 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
<<<<<<< .mine
		{ 0.0f, 100.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 100.0f, 100.0f, 0.2f, 0.0f },
=======
		{ 0.0f, size, 0.0f, 0.0f, 0.0f },
		{ 0.0f, size, size, 0.2f, 0.0f },
>>>>>>> .r72


		//up
<<<<<<< .mine
		{ 0.0f, 100.0f, 0.0f, 1.0f, 1.0f },
		{ 0.0f, 100.0f, 100.0f, 1.0f, 0.0f },
		{ 100.0f, 100.0f, 100.0f, 0.8f, 0.0f },
=======
		{ 0.0f, size, 0.0f, 1.0f, 1.0f },
		{ 0.0f, size, size, 1.0f, 0.0f },
		{ size, size, size, 0.8f, 0.0f },
>>>>>>> .r72

<<<<<<< .mine
		{ 0.0f, 100.0f, 0.0f, 1.0f, 1.0f },
		{ 100.0f, 100.0f, 0.0f, 0.8f, 1.0f },
		{ 100.0f, 100.0f, 100.0f, 0.8f, 0.0f },
=======
		{ 0.0f, size, 0.0f, 1.0f, 1.0f },
		{ size, size, 0.0f, 0.8f, 1.0f },
		{ size, size, size, 0.8f, 0.0f },
>>>>>>> .r72


		//front
		{ 0.0f, 0.0f, 0.0f, 0.8f, 1.0f },
<<<<<<< .mine
		{ 0.0f, 100.0f, 0.0f, 0.8f, 0.0f },
		{ 100.0f, 100.0f, 0.0f, 0.6f, 0.0f },
=======
		{ 0.0f, size, 0.0f, 0.8f, 0.0f },
		{ size, size, 0.0f, 0.6f, 0.0f },
>>>>>>> .r72
		
		{ 0.0f, 0.0f, 0.0f, 0.8f, 1.0f },
<<<<<<< .mine
		{ 100.0f, 100.0f, 0.0f, 0.6f, 0.0f },
		{ 100.0f, 0.0f, 0.0f, 0.6f, 1.0f },
=======
		{ size, size, 0.0f, 0.6f, 0.0f },
		{ size, 0.0f, 0.0f, 0.6f, 1.0f },
>>>>>>> .r72
		
    };
	
	
	CUSTOMVERTEX* cv_Vertices = new CUSTOMVERTEX[36];

	for (int i = 0; i < 36; i++)
	{
		cv_Vertices[i].x = vertices[i].x;
		cv_Vertices[i].y = vertices[i].y;
		cv_Vertices[i].z = vertices[i].z;
		cv_Vertices[i].fU = vertices[i].fU;
		cv_Vertices[i].fV = vertices[i].fV;
	}


	std::string id = "Skybox";
	int amount = 36;

	renderer->createVertexBuffer(amount, id, cv_Vertices);

	return S_OK;
}

// Does the rendering of the skybox.
void SceneSkybox::render()
{
	//set texture
	renderer->setTexture(texture);
	
    // Draw the triangles in the vertex buffer. 
	// We are passing the vertices down a "stream".
	// We let the D3D know what vertex shader to use.
	// We call the DrawPrimitive which does the renderering.
	renderer->setStreamSource("Skybox");
	renderer->setFvf();
	renderer->zBufferDisable();
	renderer->setupWorldMatrix();
	renderer->drawPrimitive();
	renderer->zBufferEnable();
}

