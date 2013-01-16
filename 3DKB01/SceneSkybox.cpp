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

	InitVB();

	LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9) directX->getDevice();

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->SetRenderState(D3DRS_ZENABLE, TRUE );

}


// Initialize vertices for rendering a skybox
HRESULT SceneSkybox::InitVB()
{
   LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9) directX->getDevice();
	
	
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

    // Create the vertex buffer.
    // (from the default pool) to hold all our 3 custom vertices. We also
    // specify the FVF, so the vertex buffer knows what data it contains.
	if( FAILED( device->CreateVertexBuffer( 36 * sizeof( CUSTOMVERTEX ), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
    {
        return E_FAIL;
    }

	// Fill the vertex buffer.
	// To do this, we need to Lock() the VB to
    // gain access to the vertices. 
	// This mechanism is required because vertex
    // buffers may be in device memory.
    VOID* pVertices;
    if( FAILED( g_pVB->Lock( 0, sizeof( vertices ), ( void** )&pVertices, 0 ) ) )
        return E_FAIL;
    memcpy( pVertices, vertices, sizeof( vertices ) );
    g_pVB->Unlock();

    return S_OK;
}

// Does the rendering of the skybox.
void SceneSkybox::Render()
{
	LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9) directX->getDevice();

	//load texture from file
	D3DXCreateTextureFromFile(device,
                          "textures/skybox.png",
                          &texture);

	//set texture
	device->SetTexture(0, texture);

	
    // Draw the triangles in the vertex buffer. 
	// We are passing the vertices down a "stream".
	// We let the D3D know what vertex shader to use.
	// We call the DrawPrimitive which does the renderering.
	device->SetStreamSource(0, g_pVB, 0, sizeof( CUSTOMVERTEX ) );
	device->SetFVF( D3DFVF_CUSTOMVERTEX );
	device->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 16 );
}

