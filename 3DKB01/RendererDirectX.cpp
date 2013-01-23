#include "RendererDirectX.h"

RendererDirectX::RendererDirectX(void)
{

};

/*
/ Destroy the instance of the object from this class.
*/
RendererDirectX::~RendererDirectX(void)
{
	//directX = NULL;
};

/*
/ Initialize the Direct3D
/ This method first creates the D3D object, then
/ sets up the structure used to create the D3DDevice,
/ which is created afterwards. At last culling and D3D
/ lighting is turned off, so that it's possible to see
/ both sides of the triangle(s) and to use our own vertex
/ colors. Turn on the zbuffer for the more complex geometry.
*/
HRESULT RendererDirectX::initD3D(HWND hWnd)
{
	if(0 == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	LPDIRECT3DSWAPCHAIN9 swapChain = NULL;
	swapChainMap.insert(std::pair<std::string, LPDIRECT3DSWAPCHAIN9>("swap1", swapChain));
	swapChainMap.insert(std::pair<std::string, LPDIRECT3DSWAPCHAIN9>("swap2", swapChain));

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferWidth = 1920;
	d3dpp.BackBufferHeight = 1080;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	

	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// After the device was created, this first swappchain already exists.
	LPDIRECT3DSWAPCHAIN9 swapChain1 = getSwapChain("swap1");
	LPDIRECT3DSWAPCHAIN9 swapChain2 = getSwapChain("swap2");

	g_pd3dDevice->GetSwapChain(0, &swapChain1);
	// Create and additional swap chain to render to another window.
	g_pd3dDevice->CreateAdditionalSwapChain(&d3dpp, &swapChain2);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	// Enable swapping between windows.
	g_pd3dDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE );
	
//	g_pd3dDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);

	return S_OK;
};

void RendererDirectX::cleanUp(void)
{
	if(getSwapChain("swap1") != 0)
		getSwapChain("swap1")->Release();
	if(getSwapChain("swap2") != 0)
		getSwapChain("swap2")->Release();
	if(g_pd3dDevice != 0)
		g_pd3dDevice->Release();
	if(g_pD3D != 0)
		g_pD3D->Release();
};

/*
/ This method builds the world, view and projection transform matrices.
/ D3DXMATRIXA16 is set to make the object rotate about the y-axis.
/ Next the rotation matrix is set to generate a full rotation(2*PI radians).
/ After the view matrix is set up and defined by giving it and eye point,
/ from where it is being looked at. At last a perspective transform is set up.
*/
void RendererDirectX::setupCamera(const D3DXVECTOR3* eyePT, const D3DXVECTOR3* Lookat)
{
	//D3DXMATRIXA16 matWorld;

	//UINT iTime = timeGetTime() / 5;
	//FLOAT fAngle = iTime * (1.0f * D3DX_PI) / 4000.0f;
	//D3DXMatrixTranslation(&matWorld, 0.0f , 0.0f , 0.0f);
	//D3DXMatrixRotationY(&matWorld, fAngle);
	//g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	
	D3DXVECTOR3 vUp( 0,1,0 );

	//D3DXVECTOR3 vEyePt(0.0f, 8.0f, 12.0f);
	//D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, eyePT, Lookat, &vUp);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj); // probably needs to be outside the programloop.
}

void RendererDirectX::setupWorldMatrix(Vector position, Vector orientation)
{
	
	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matTranslation;
	D3DXMATRIXA16 matOrientation;

	D3DXMatrixRotationY(&matOrientation, orientation.getY());
	
	D3DXMatrixTranslation(&matTranslation, position.getX(), position.getY(), position.getZ());
	D3DXMatrixMultiply(&matWorld, &matOrientation, &matTranslation);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
}


void RendererDirectX::beginScene()
{
	g_pd3dDevice->BeginScene();
}

void RendererDirectX::endScene()
{
	g_pd3dDevice->EndScene();
}

void RendererDirectX::clear()
{
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_XRGB( 122, 50, 202 ), 1.0f, 0 );
}

void RendererDirectX::present()
{
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

void RendererDirectX::setFvf(std::string argType)
{
	
//	if(argType.compare("Skybox") == 0)
//	{
		g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
//	}
//	else if (argType.compare("Terrain") == 0)
//	{
//		g_pd3dDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
//	}
}

void RendererDirectX::setTexture(ResourceTexture* argTexture)
{
	LPDIRECT3DTEXTURE9 texture = argTexture->getMeshTextures();
	g_pd3dDevice->SetTexture(0, texture);
}

void RendererDirectX::drawPrimitive()
{
	g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 12 );


}

// Create the vertex buffer.
// (from the default pool) to hold all our 3 custom vertices. We also
// specify the FVF, so the vertex buffer knows what data it contains.
void RendererDirectX::createVertexBuffer(int argSize, std::string argType, CUSTOMVERTEX* argVertices )
{
	LPDIRECT3DVERTEXBUFFER9 vertexbuffer = NULL;

//	if (argType.compare("Skybox") == 0)
//	{
//		//skybox
		g_pd3dDevice->CreateVertexBuffer( argSize * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &vertexbuffer, NULL );
//	}
//	else if(argType.compare("Terrain") == 0)
//	{
//		//terrain
//		g_pd3dDevice->CreateVertexBuffer( argSize * sizeof(CUSTOMVERTEX), 0, D3DFVF_XYZ|D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &vertexbuffer, NULL);
//	}
//
	// Fill the vertex buffer.
	// To do this, we need to Lock() the VB to
    // gain access to the vertices. 
	// This mechanism is required because vertex
    // buffers may be in device memory.
	
	VOID* pVertices;
	vertexbuffer->Lock( 0, argSize*sizeof( CUSTOMVERTEX ), ( void** )&pVertices, 0 );
	
	memcpy( pVertices, argVertices, argSize*sizeof( CUSTOMVERTEX ) );
	vertexbuffer->Unlock();

	
	vertexBufferMap.insert(std::pair<std::string, LPDIRECT3DVERTEXBUFFER9>(argType, vertexbuffer));
}

void RendererDirectX::createIndexBuffer(int argSize, const std::string& argType, short* argIndices)
{
	LPDIRECT3DINDEXBUFFER9 indexbuffer = NULL;
	
	g_pd3dDevice->CreateIndexBuffer(argSize*sizeof(short),D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&indexbuffer,NULL);

    VOID* p_Indices;
	indexbuffer->Lock(0, argSize*sizeof(short), (void**)&p_Indices, 0);

    memcpy(p_Indices, argIndices, argSize*sizeof(short));
    indexbuffer->Unlock();
   
	indexBufferMap.insert(std::pair<std::string, LPDIRECT3DINDEXBUFFER9>(argType, indexbuffer));
}


void RendererDirectX::drawIndexedPrimitive(float terSide, float terFront, float terUp, int argWidth, int argHeight)
{
	
	D3DXMATRIX m_Rotation;
    D3DXMatrixRotationY(&m_Rotation, 0 );

	D3DXMATRIX m_Translation;
    D3DXMatrixTranslation(&m_Translation, terSide, terFront, terUp);

    D3DXMATRIX m_World;
    D3DXMatrixMultiply(&m_World, &m_Translation, &m_Rotation);
    g_pd3dDevice->SetTransform(D3DTS_WORLD, &m_World);
	
	g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,argWidth*argHeight,0,(argWidth-1)*(argHeight-1)*2);
}

void RendererDirectX::setStreamSource(std::string argType)
{
	LPDIRECT3DVERTEXBUFFER9 vertexbuffer = NULL;

	std::map<std::string, LPDIRECT3DVERTEXBUFFER9>::iterator Iterator;
	for(Iterator = vertexBufferMap.begin(); Iterator != vertexBufferMap.end(); ++Iterator) 
	{
		if (Iterator->first.compare(argType) == 0 )
		{
			vertexbuffer = Iterator->second;
		}
	}
	g_pd3dDevice->SetStreamSource( 0, vertexbuffer, 0, sizeof(CUSTOMVERTEX) );
}

void RendererDirectX::setIndices(std::string argType)
{
	LPDIRECT3DINDEXBUFFER9 indexbuffer = NULL;
	
	std::map<std::string, LPDIRECT3DINDEXBUFFER9>::iterator Iterator;
	for(Iterator = indexBufferMap.begin(); Iterator != indexBufferMap.end(); ++Iterator) 
	{
		if (Iterator->first.compare(argType) == 0 )
		{
			indexbuffer = Iterator->second;
		}
	}
	g_pd3dDevice->SetIndices(indexbuffer);
}


LPDIRECT3DDEVICE9 RendererDirectX::getDevice() {
	return g_pd3dDevice;
};

LPDIRECT3DSWAPCHAIN9 RendererDirectX::getSwapChain(std::string arg)
{
	std::map<std::string, LPDIRECT3DSWAPCHAIN9>::iterator iter = swapChainMap.find(arg);
	return iter->second;
}

