#include "SceneSkybox.h"
#include "Resourcemanager.h"


SceneSkybox::SceneSkybox()
{
	initialize();
}


SceneSkybox::SceneSkybox(RendererInterface* argRendererDirectX, ResourceTexture* argTexture)
{
	renderer = argRendererDirectX;
	texture = argTexture;
	initialize();
}


SceneSkybox::~SceneSkybox(void)
{
}

void SceneSkybox::initialize()
{
	initVB();
}

HRESULT SceneSkybox::initVB()
{
	
	
	CUSTOMVERTEX vertices[] =
    {
       	//bottom
		{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f, 0.0f, 0.0f },

		{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f },


		//back
		{ 0.0f, 0.0f, 1.0f, 0.2f, 1.0f },
		{ 0.0f, 1.0f, 1.0f, 0.2f, 0.0f },
		{ 1.0f, 1.0f, 1.0f, 0.4f, 0.0f },

		{ 0.0f, 0.0f, 1.0f, 0.2f, 1.0f },
		{ 1.0f, 0.0f, 1.0f, 0.4f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 0.4f, 0.0f },


		//right
		{ 1.0f, 0.0f, 0.0f, 0.6f, 1.0f },
		{ 1.0f, 1.0f, 0.0f, 0.6f, 0.0f },
		{ 1.0f, 1.0f, 1.0f, 0.4f, 0.0f },

		{ 1.0f, 0.0f, 0.0f, 0.6f, 1.0f },
		{ 1.0f, 0.0f, 1.0f, 0.4f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 0.4f, 0.0f },


		//left
		{ 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 0.2f, 1.0f },
		{ 0.0f, 1.0f, 1.0f, 0.2f, 0.0f },

		{ 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 1.0f, 0.2f, 0.0f },


		//up
		{ 0.0f, 1.0f, 0.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 1.0f, 1.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f, 0.8f, 0.0f },

		{ 0.0f, 1.0f, 0.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 0.0f, 0.8f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 0.8f, 0.0f },


		//front
		{ 0.0f, 0.0f, 0.0f, 0.8f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 0.8f, 0.0f },
		{ 1.0f, 1.0f, 0.0f, 0.6f, 0.0f },
		
		{ 0.0f, 0.0f, 0.0f, 0.8f, 1.0f },
		{ 1.0f, 1.0f, 0.0f, 0.6f, 0.0f },
		{ 1.0f, 0.0f, 0.0f, 0.6f, 1.0f },
		
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

	/*
    //bottom
	cv_Vertices[0] = CUSTOMVERTEX(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	cv_Vertices[1] = CUSTOMVERTEX(0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	cv_Vertices[2] = CUSTOMVERTEX( 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
						  
	cv_Vertices[3] = CUSTOMVERTEX( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	cv_Vertices[4] = CUSTOMVERTEX( 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	cv_Vertices[5] = CUSTOMVERTEX( 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			
	//back
	cv_Vertices[6] = CUSTOMVERTEX( 0.0f, 0.0f, 1.0f, 0.2f, 1.0f);
	cv_Vertices[7] = CUSTOMVERTEX( 0.0f, 1.0f, 1.0f, 0.2f, 0.0f);
	cv_Vertices[8] = CUSTOMVERTEX( 1.0f, 1.0f, 1.0f, 0.4f, 0.0f);

	cv_Vertices[9] = CUSTOMVERTEX( 0.0f, 0.0f, 1.0f, 0.2f, 1.0f);
	cv_Vertices[10] = CUSTOMVERTEX( 1.0f, 0.0f, 1.0f, 0.4f, 1.0f);
	cv_Vertices[11] = CUSTOMVERTEX( 1.0f, 1.0f, 1.0f, 0.4f, 0.0f);

	//right
	vertices[12] = CUSTOMVERTEX( 1.0f, 0.0f, 0.0f, 0.6f, 1.0f);
	vertices[13] = CUSTOMVERTEX( 1.0f, 1.0f, 0.0f, 0.6f, 0.0f);
	vertices[14] = CUSTOMVERTEX( 1.0f, 1.0f, 1.0f, 0.4f, 0.0f);

	vertices[15] = CUSTOMVERTEX( 1.0f, 0.0f, 0.0f, 0.6f, 1.0f);
	vertices[16] = CUSTOMVERTEX( 1.0f, 0.0f, 1.0f, 0.4f, 1.0f);
	vertices[17] = CUSTOMVERTEX( 1.0f, 1.0f, 1.0f, 0.4f, 0.0f);

	//left						  
	vertices[18] = CUSTOMVERTEX( 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	vertices[19] = CUSTOMVERTEX( 0.0f, 0.0f, 1.0f, 0.2f, 1.0f);
	vertices[20] = CUSTOMVERTEX( 0.0f, 1.0f, 1.0f, 0.2f, 0.0f);
						   
	vertices[21] = CUSTOMVERTEX( 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	vertices[22] = CUSTOMVERTEX( 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	vertices[23] = CUSTOMVERTEX( 0.0f, 1.0f, 1.0f, 0.2f, 0.0f);

	//up
	vertices[24] = CUSTOMVERTEX( 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	vertices[25] = CUSTOMVERTEX( 0.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	vertices[26] = CUSTOMVERTEX( 1.0f, 1.0f, 1.0f, 0.8f, 0.0f);
						  
	vertices[27] = CUSTOMVERTEX( 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	vertices[28] = CUSTOMVERTEX( 1.0f, 1.0f, 0.0f, 0.8f, 1.0f);
	vertices[29] = CUSTOMVERTEX( 1.0f, 1.0f, 1.0f, 0.8f, 0.0f);
															 
	//front													 
	vertices[30] = CUSTOMVERTEX( 0.0f, 0.0f, 0.0f, 0.8f, 1.0f);
	vertices[31] = CUSTOMVERTEX( 0.0f, 1.0f, 0.0f, 0.8f, 0.0f);
	vertices[32] = CUSTOMVERTEX( 1.0f, 1.0f, 0.0f, 0.6f, 0.0f);
															 
	vertices[33] = CUSTOMVERTEX( 0.0f, 0.0f, 0.0f, 0.8f, 1.0f);
	vertices[34] = CUSTOMVERTEX( 1.0f, 1.0f, 0.0f, 0.6f, 0.0f);
	vertices[35] = CUSTOMVERTEX( 1.0f, 0.0f, 0.0f, 0.6f, 1.0f);
*/
	
	std::string id = "Skybox";
	int amount = 36;

	renderer->createVertexBuffer(amount, id, cv_Vertices);

	/*
	if( FAILED( g_pd3dDevice->CreateVertexBuffer( 36 * sizeof( CUSTOMVERTEXSKYBOX ), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
    {
        return E_FAIL;
    }
	*/
	return S_OK;
}

// Does the rendering of the skybox.
void SceneSkybox::Render()
{
	//LPDIRECT3DTEXTURE9 texture = NULL;

	//load texture from file
	//D3DXCreateTextureFromFile(device, "textures/skybox.png", &texture);
	
	
	
	//set texture
	renderer->setTexture(texture);
	
    // Draw the triangles in the vertex buffer. 
	// We are passing the vertices down a "stream".
	// We let the D3D know what vertex shader to use.
	// We call the DrawPrimitive which does the renderering.

	renderer->setStreamSource("Skybox");
	renderer->setFvf("Skybox");
	renderer->zBufferDisable();
	renderer->drawPrimitive();
	renderer->zBufferEnable();
	//directX->zBufferEnable();
}

