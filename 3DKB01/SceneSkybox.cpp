#include "SceneSkybox.h"



SceneSkybox::SceneSkybox()
{
	initialize();
}


SceneSkybox::SceneSkybox(RendererDirectX* argRendererDirectX)
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
	g_pVB = NULL;

	InitVB();

	directX->getDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	directX->getDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	directX->getDevice()->SetRenderState(D3DRS_ZENABLE, TRUE );

}

HRESULT SceneSkybox::InitVB()
{
    // Initialize three vertices for rendering a triangle
    CUSTOMVERTEX vertices[] =
    {
        { 1.0f, 33.0f, 0.0f,  0xffff0000, }, // x, y, z , color
		{ 2.0f, 50.0f, 0.0f,  0xffffffff, },
        { 3.0f, 50.0f, 0.0f,  0xff00ffff, },
    };

    // Create the vertex buffer. Here we are allocating enough memory
    // (from the default pool) to hold all our 3 custom vertices. We also
    // specify the FVF, so the vertex buffer knows what data it contains.
	if( FAILED( directX->getDevice()->CreateVertexBuffer( 3 * sizeof( CUSTOMVERTEX ),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
    {
        return E_FAIL;
    }

    // Now we fill the vertex buffer. To do this, we need to Lock() the VB to
    // gain access to the vertices. This mechanism is required becuase vertex
    // buffers may be in device memory.
    VOID* pVertices;
    if( FAILED( g_pVB->Lock( 0, sizeof( vertices ), ( void** )&pVertices, 0 ) ) )
        return E_FAIL;
    memcpy( pVertices, vertices, sizeof( vertices ) );
    g_pVB->Unlock();

    return S_OK;
}


VOID SceneSkybox::Render()
{
        // Draw the triangles in the vertex buffer. This is broken into a few
        // steps. We are passing the vertices down a "stream", so first we need
        // to specify the source of that stream, which is our vertex buffer. Then
        // we need to let D3D know what vertex shader to use. Full, custom vertex
        // shaders are an advanced topic, but in most cases the vertex shader is
        // just the FVF, so that D3D knows what type of vertices we are dealing
        // with. Finally, we call DrawPrimitive() which does the actual rendering
        // of our geometry (in this case, just one triangle).
	directX->getDevice()->SetStreamSource(0, g_pVB, 0, sizeof( CUSTOMVERTEX ) );
	directX->getDevice()->SetFVF( D3DFVF_CUSTOMVERTEX );
	directX->getDevice()->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 1 );

}

