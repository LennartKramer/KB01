#include "RendererDirectX.h"

RendererDirectX::RendererDirectX(void)
{
};

RendererDirectX::~RendererDirectX(void)
{
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
void RendererDirectX::initD3D(HWND hWnd)
{
	HRESULT result;
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

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
	

	g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice);


	// After the device was created, this first swappchain already exists.
//	LPDIRECT3DSWAPCHAIN9 swapChain1 = getSwapChain("swap1");
//	LPDIRECT3DSWAPCHAIN9 swapChain2 = getSwapChain("swap2");

	//g_pd3dDevice->GetSwapChain(0, &swapChain1);
	// Create and additional swap chain to render to another window.
	//g_pd3dDevice->CreateAdditionalSwapChain(&d3dpp, &swapChain2);
	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	// Enable swapping between windows.
	//g_pd3dDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE );
	
//	g_pd3dDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);

};

void RendererDirectX::cleanUp(void)
{
//	if(getSwapChain("swap1") != 0)
//		getSwapChain("swap1")->Release();
//	if(getSwapChain("swap2") != 0)
//		getSwapChain("swap2")->Release();
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


void RendererDirectX::updateCamera(Vector* eyePt, Vector* lookatPt, float cameraYawAngle, float cameraPitchAngle)
{

	 // Make a rotation matrix based on the camera's yaw & pitch
	D3DXMATRIX cameraRot;
    D3DXMatrixRotationYawPitchRoll( &cameraRot, cameraYawAngle, cameraPitchAngle, 0 );

	// Transform vectors based on camera's rotation matrix
    D3DXVECTOR3 vWorldUp, vWorldAhead;
    D3DXVECTOR3 vLocalUp = D3DXVECTOR3( 0, 1, 0 );
    D3DXVECTOR3 vLocalAhead = D3DXVECTOR3( 0, 0, 1 );
    D3DXVec3TransformCoord( &vWorldUp, &vLocalUp, &cameraRot );
    D3DXVec3TransformCoord( &vWorldAhead, &vLocalAhead, &cameraRot );


	// Update the lookAt position based on the eye position 
	lookatPt->x = eyePt->x + vWorldAhead.x;
	lookatPt->y= eyePt->y + vWorldAhead.y;
	lookatPt->z = eyePt->z + vWorldAhead.z;
	

	//set Matrix for Eye and Lookat
	D3DXVECTOR3 mEye(eyePt->x,eyePt->y,eyePt->z);
	D3DXVECTOR3 mLookAt(lookatPt->x,lookatPt->y,lookatPt->z);

	// Update the view matrix
    D3DXMatrixLookAtLH( &m_mView, &mEye, &mLookAt, &vWorldUp );
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &m_mView);
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 0.1f, 1000.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj); // probably needs to be outside the programloop.
}

// Create an empty deafault world matrix with no orientation or translation.
void RendererDirectX::setupWorldMatrix()
{

	D3DXMATRIXA16	matOrientation;
	D3DXMATRIXA16	matTranslation;
	D3DXMATRIXA16	matWorld;
	D3DXMatrixRotationX(&matOrientation, 0.0f);
	D3DXMatrixRotationY(&matOrientation, 0.0f);
	D3DXMatrixRotationZ(&matOrientation, 0.0f);

	D3DXMatrixTranslation(&matTranslation,  0.0f,  0.0f, 0.0f);
	
	D3DXMatrixMultiply(&matWorld, &matOrientation, &matTranslation);

	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
}

// Move the matrix to a certain Orientation and position
void RendererDirectX::moveMatrix(Vector argOrientation, Vector argPosition)
{
	D3DXMATRIXA16	matOrientation;
	D3DXMATRIXA16	matTranslation;
	D3DXMATRIXA16	matWorld;

	D3DXMatrixRotationX(&matOrientation, argOrientation.getX());
	D3DXMatrixRotationY(&matOrientation, argOrientation.getY());
	D3DXMatrixRotationZ(&matOrientation, argOrientation.getZ());
	
	D3DXMatrixTranslation(&matTranslation, argPosition.getX(), argPosition.getY(), argPosition.getZ());
	D3DXMatrixMultiply(&matWorld, &matOrientation, &matTranslation);

	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
}


//Applications must call IDirect3DDevice9::BeginScene before performing any rendering 
void RendererDirectX::setupViewMatrix(Vector eyePt, Vector lookatPt)
{
	//set Matrix for Eye and Lookat
	D3DXVECTOR3 Eye(eyePt.x,eyePt.y,eyePt.z);
	D3DXVECTOR3 LookAt(lookatPt.x,lookatPt.y,lookatPt.z);

    // Calc the view matrix
    D3DXVECTOR3 vUp( 0,1,0 );
    D3DXMatrixLookAtLH( &m_mView, &Eye, &LookAt, &vUp );
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &m_mView);
}


void RendererDirectX::setupProjectionMatrix( FLOAT fFOV, FLOAT fAspect, FLOAT fNearPlane,
                                 FLOAT fFarPlane)
{
    D3DXMatrixPerspectiveFovLH( &m_mProj, fFOV, fAspect, fNearPlane, fFarPlane );
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_mProj);
}

void RendererDirectX::beginScene()
{
	g_pd3dDevice->BeginScene();
}

//and must call IDirect3DDevice9::EndScene when rendering is complete and before calling IDirect3DDevice9::BeginScene again.
void RendererDirectX::endScene()
{
	g_pd3dDevice->EndScene();
}

//Clears one or more surfaces such as a render target, multiple render targets, a stencil buffer, and a depth buffer.
void RendererDirectX::clear()
{
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_XRGB( 122, 50, 202 ), 1.0f, 0 );
}

//Presents the contents of the next buffer in the sequence of back buffers owned by the device.
void RendererDirectX::present()
{
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

//Sets the current vertex stream declaration.
void RendererDirectX::setFvf()
{
	g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
}

//Assigns a texture to a stage for a device.
void RendererDirectX::setTexture(ResourceTexture* argTexture)
{
	LPDIRECT3DTEXTURE9 texture = argTexture->getMeshTextures();
	g_pd3dDevice->SetTexture(0, texture);
}

//Renders a sequence of nonindexed, geometric primitives of the specified type from the current set of data input streams.
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

	g_pd3dDevice->CreateVertexBuffer( argSize * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &vertexbuffer, NULL );

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

// This method draws indexed primitives from the current set of data input streams. 
void RendererDirectX::drawIndexedPrimitive(int argWidth, int argHeight)
{
	g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,argWidth*argHeight,0,(argWidth-1)*(argHeight-1)*2);
}

// Binds a vertex buffer to a device data stream.
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

// The SetIndices method sets the current index array to an index buffer. The single set of indices is used to index all streams. 
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

/*
LPDIRECT3DSWAPCHAIN9 RendererDirectX::getSwapChain(std::string arg)
{
	std::map<std::string, LPDIRECT3DSWAPCHAIN9>::iterator iter = swapChainMap.find(arg);
	return iter->second;
}
*/
void RendererDirectX::zBufferEnable(void) 
{ 
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE );
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE); 
}

void RendererDirectX::zBufferDisable(void) 
{ 
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE );
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE); 
}

void* RendererDirectX::getDevice()
{
	return g_pd3dDevice;
}