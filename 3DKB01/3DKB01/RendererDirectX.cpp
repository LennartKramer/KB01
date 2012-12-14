#include "RendererDirectX.h"
#include "RendererInterface.h"
#include "CustomVertex.h"

RendererDirectX::RendererDirectX()
{
	// Leave empty for now.
};

/*
/ Destroy the instance of the object from this class.
*/
RendererDirectX::~RendererDirectX()
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
/ colors.
*/
HRESULT RendererDirectX::initD3D(HWND hWnd)
{
	if(0 == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
};

/*
/ This method builds the geometry of the current scene
/ It uses the include of CustomVertex when the coördinates
/ and Color are defined. After the coördinates are declared,
/ a vertex buffer is created and then filled.
*/
HRESULT RendererDirectX::initGeometry(void)
{
	Vertex_UD vertices[] =
	{
		{  1.0f, 0.0f, 0.0f, 0xffffff00, },
		{ -1.0, 0.0f, 0.0f, 0xffffff00,  },
		{  0.0, 0.0f, 1.0f, 0xffffff00,  },
	};


	g_pd3dDevice->CreateVertexBuffer(
		// UINT length - The size of our new vertex buffer, in bytes.
		sizeof(vertices),
		// DWORD Usage - Some usage flags to set up.
		D3DUSAGE_WRITEONLY,
		// DWORD FVF - The Vertex Format to use for this buffer.
		vertices[0].FORMAT,
		// D3DPOOL Pool - What memory resource to use for this buffer.
		D3DPOOL_DEFAULT,
		// IDirect3DVertexBuffer9** ppVertexBuffer - The vertex buffer to create.
		&g_pVB,
		// HANDLE* pSharedHandle - Reserved. Must be NULL.
		NULL);

	void* bufferMemory;

	// Place the lock on the buffer to get the pointer.
	g_pVB->Lock(
		// UINT OffsetToLock - At what index, in bytes, to place the lock.
		0,
		// UINT SizeToLock - How many bytes of memory to lock.
		sizeof(vertices),
		// void** ppbData - The resulting pointer to write.
		&bufferMemory,
		// DWORD flags - Some special flags to use in obtaining the lock.
		NULL);

	memcpy(bufferMemory, vertices, sizeof(vertices));

	g_pVB->Unlock();

	g_pd3dDevice->SetFVF(vertices[0].FORMAT);

	g_pd3dDevice->SetStreamSource(
		// UINT StreamNumber - Which stream to set this to.
		0,
		// IDirect3DVertexBuffer9* pStreamData - The vertex buffer to use.
		g_pVB,
		// UINT OffsetInBytes - The offset to start reading from, in bytes.
		0,
		// UINT Stride - The size of a single vertex.
		vertices[0].STRIDE_SIZE);

	return D3D_OK;
};

void RendererDirectX::cleanUp()
{
	if(g_pVB != 0)
		g_pVB->Release();
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
void RendererDirectX::setupMatrices()
{
	D3DXMATRIXA16 matWorld;

	UINT iTime = timeGetTime() / 5;
	FLOAT fAngle = iTime * (1.0f * D3DX_PI) / 4000.0f;
	D3DXMatrixRotationY(&matWorld, fAngle);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3 vEyePt(0.0f, 2.0f, -2.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
};

/*
/ Clear the backbuffer to a black color and then draw the scene.
/ Present the backbuffer contents to the display(backbuffer -> frontbuffer).
*/
void RendererDirectX::render()
{
	g_pd3dDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);

	if(SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		setupMatrices();

		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

		g_pd3dDevice->EndScene();
	}
	g_pd3dDevice->Present(0, 0, 0, 0);
};