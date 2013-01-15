#include "RendererDirectX.h"
#include "CustomVertex.h"

RendererDirectX::RendererDirectX(void)
{
	g_pIB = NULL;
	g_pVB = NULL;
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

	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE );
	
	g_pd3dDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);

	return S_OK;
};


void RendererDirectX::cleanUp(void)
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
void RendererDirectX::setupCamera(Vector argPosition, Vector argDirection, Vector argUp)
{
	//D3DXMATRIXA16 matWorld;

	//UINT iTime = timeGetTime() / 5;
	//FLOAT fAngle = iTime * (1.0f * D3DX_PI) / 4000.0f;
	//D3DXMatrixTranslation(&matWorld, 0.0f , 0.0f , 0.0f);
	//D3DXMatrixRotationY(&matWorld, fAngle);
	//g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	

	D3DXVECTOR3 position;
	position.x = argPosition.getX() ;
	position.y = argPosition.getY() ;
	position.z = argPosition.getZ() ;

	D3DXVECTOR3 direction ;
	direction.x = argDirection.getX() ;
	direction.y = argDirection.getY() ;
	direction.z = argDirection.getZ() ;

	D3DXVECTOR3 up;
	up.x = argUp.getX();
	up.y = argUp.getY();
	up.z = argUp.getZ();

	//D3DXVECTOR3 vEyePt(0.0f, 8.0f, 12.0f);
	//D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &position, &direction, &up);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
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

void RendererDirectX::setFvf()
{
	g_pd3dDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
}

void RendererDirectX::setTexture(ResourceTexture* argTexture)
{
	LPDIRECT3DTEXTURE9* texture = argTexture->getMeshTextures();
	g_pd3dDevice->SetTexture(0, (  (*texture)  ));
}

void RendererDirectX::fillIndices(int argOffset, int argHeight, int argWidth)
{
	int WIDTH = argWidth;
	int HEIGHT = argHeight;

    short *s_Indices = new short[(WIDTH-1)*(HEIGHT-1)*6];

    for (int x=0;x< WIDTH-1;x++)    {


        for (int y=0; y< HEIGHT-1;y++)        {
            s_Indices[(x+y*(WIDTH-1))*6+2] = x+y*WIDTH;
            s_Indices[(x+y*(WIDTH-1))*6+1] = (x+1)+y*WIDTH;
            s_Indices[(x+y*(WIDTH-1))*6] = (x+1)+(y+1)*WIDTH;

            s_Indices[(x+y*(WIDTH-1))*6+3] = (x+1)+(y+1)*WIDTH;
            s_Indices[(x+y*(WIDTH-1))*6+4] = x+y*WIDTH;
            s_Indices[(x+y*(WIDTH-1))*6+5] = x+(y+1)*WIDTH;
        }
    }

    if (FAILED(g_pd3dDevice->CreateIndexBuffer((WIDTH-1)*(HEIGHT-1)*6*sizeof(short),D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&g_pIB,NULL)))
    {
       
    }

    VOID* p_Indices;
    if (FAILED(g_pIB->Lock(0, (WIDTH-1)*(HEIGHT-1)*6*sizeof(short), (void**)&p_Indices, 0)))
    {
        
    }else{
        memcpy(p_Indices, s_Indices, (WIDTH-1)*(HEIGHT-1)*6*sizeof(short));
        g_pIB->Unlock();
    }
    delete [] s_Indices;
}


struct OURCUSTOMVERTEX
{
    float x,y,z;
    DWORD color;
};

void RendererDirectX::fillVertices(int argOffset, int argHeight, int argWidth)
{
	int offset = argOffset;
	int WIDTH = argWidth;
	int HEIGHT = argHeight;
	
    OURCUSTOMVERTEX *cv_Vertices = new OURCUSTOMVERTEX[WIDTH*WIDTH];

    std::ifstream f_DataFile;
    short unsigned int dummy;
    f_DataFile.open("heightmap.bmp", std::ios::binary);
    if (f_DataFile.is_open())
    {

        for (int i = 0;i< (offset);i++)        {
            dummy = f_DataFile.get();
        }

        for (int x=0;x< WIDTH;x++)        {

            for (int y=0; y< HEIGHT;y++)            {
                int height = f_DataFile.get();
                height += f_DataFile.get();
                height += f_DataFile.get();
                height /= 8;
                cv_Vertices[y*WIDTH + x].x = -x;
                cv_Vertices[y*WIDTH + x].y = y;
                cv_Vertices[y*WIDTH + x].z = height;
                cv_Vertices[y*WIDTH + x].color = 0xffffffff;
            }
        }
    }else{
        
    }

    f_DataFile.close();

	
    if (FAILED(g_pd3dDevice->CreateVertexBuffer(WIDTH*HEIGHT*sizeof(OURCUSTOMVERTEX), 0, D3DFVF_XYZ|D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &g_pVB, NULL)))
    {        
       
    }
	

    VOID* p_Vertices;
    if (FAILED(g_pVB->Lock(0, WIDTH*HEIGHT*sizeof(OURCUSTOMVERTEX), (void**)&p_Vertices, 0)))
    {
        
    }else{
        memcpy(p_Vertices, cv_Vertices, WIDTH*HEIGHT*sizeof(OURCUSTOMVERTEX));
        g_pVB->Unlock();
    }
    delete [] cv_Vertices;
}

void RendererDirectX::drawPrimitive(float terSide, float terFront, float terUp, int argWidth, int argHeight)
{
	
	D3DXMATRIX m_Rotation;
    D3DXMatrixRotationX(&m_Rotation, D3DX_PI / 2 );

	D3DXMATRIX m_Translation;
    D3DXMatrixTranslation(&m_Translation, terSide, terFront, terUp);

    D3DXMATRIX m_World;
    D3DXMatrixMultiply(&m_World, &m_Translation, &m_Rotation);
    g_pd3dDevice->SetTransform(D3DTS_WORLD, &m_World);
	
	g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,argWidth*argHeight,0,(argWidth-1)*(argHeight-1)*2);
}

void RendererDirectX::setStreamSource()
{
	g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(OURCUSTOMVERTEX) );
}

void RendererDirectX::setIndices()
{
	g_pd3dDevice->SetIndices(g_pIB);
}

/*
/ Clear the backbuffer to a black color and then draw the scene.
/ Present the backbuffer contents to the display(backbuffer -> frontbuffer).
*/

/*
void RendererDirectX::render(void* g_pMeshTextures,
	 void* g_pMesh, int bmpWidth, int bmpHeight)
{
	LPDIRECT3DTEXTURE9 texture = (LPDIRECT3DTEXTURE9) g_pMeshTextures;	
	LPD3DXMESH mesh = (LPD3DXMESH) g_pMesh ;
*/
	/*
		g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(vertex_Vertices));
		g_pd3dDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		g_pd3dDevice->SetIndices(g_pIB);

		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, bmpWidth*bmpHeight, 0,
			(bmpWidth-1)*(bmpHeight-1)*2);
		*/

		/*	
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
		*/
/*
		g_pd3dDevice->SetTexture(0, (texture));
		mesh->DrawSubset(0);
};
*/

void* RendererDirectX::getDevice(void) {
	return g_pd3dDevice;
};

/*
void RendererDirectX::initializeVertices(HWND hWnd, void* g_pd3dDevice, int bmpWidth, 
	int bmpHeight, int bmpOffset)
{
	LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9) g_pd3dDevice;

	Vertex_TD *vertex_Vertices = new Vertex_TD[bmpWidth*bmpWidth];

	std::ifstream f_DataFile;
	unsigned int dummy;
	f_DataFile.open("heightmap.bmp", std::ios::binary);

	if(f_DataFile.is_open())
	{
		for(int i = 0; i < (bmpOffset); i++)
		{
			dummy = f_DataFile.get();
		}
		for(int x = 0; x < bmpWidth; x++)
		{
			for(int y = 0; y < bmpHeight; y++)
			{
				int height = f_DataFile.get();
				height += f_DataFile.get();
				height += f_DataFile.get();
				height /= 8;
				vertex_Vertices[y*bmpWidth+x].x = -x;
				vertex_Vertices[y*bmpWidth+x].y = y;
				vertex_Vertices[y*bmpWidth+x].z = height;
				vertex_Vertices[y*bmpWidth+x].colour = 0xffffffff;
			}
		}
	}
	else
	{
		MessageBox(hWnd, "RendererDirectX fillVertices: Error while looking for heightdata.", "Error", MB_OK);
	}
	f_DataFile.close();
	

	if(FAILED( device->CreateVertexBuffer(bmpWidth*bmpHeight*sizeof(vertex_Vertices), 0,
		D3DFVF_XYZ | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &g_pVB, NULL)))
	{
		MessageBox(hWnd, "RendererDirectX fillVertices: Error while creating VertexBuffer", "Error", MB_OK);
	}

	VOID* p_Vertices;
	if(FAILED(g_pVB->Lock(0, bmpWidth*bmpHeight*sizeof(vertex_Vertices),
		(void**)&p_Vertices, 0)))
	{
		MessageBox(hWnd, "RendererirectX filLVertices: Error while trying to lock memory.", "Error", MB_OK);
	}
	else
	{
		memcpy(p_Vertices, vertex_Vertices, bmpWidth*bmpHeight*sizeof(vertex_Vertices));
		g_pVB->Unlock();
	}
	delete [] vertex_Vertices;
};

void RendererDirectX::initializeIndices(HWND hWnd, void* g_pd3dDevice, int bmpWidth, 
	int bmpHeight)
{
	LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9) g_pd3dDevice;
	
	short *s_Indices = new short[(bmpWidth-1)*(bmpHeight-1)*6];

	for(int x = 0; x < bmpWidth-1; x++)
	{
		for(int y = 0; y < bmpHeight-1; y++)
		{
			s_Indices[(x+y*(bmpWidth-1))*6+2] = x+y*bmpWidth;
			s_Indices[(x+y*(bmpWidth-1))*6+1] = (x+1)+y*bmpWidth;
			s_Indices[(x+y*(bmpWidth-1))*6] = (x+1)+(y+1)*bmpWidth;

			s_Indices[(x+y*(bmpWidth-1))*6+3] = (x+1)+(y+1)*bmpWidth;
            s_Indices[(x+y*(bmpWidth-1))*6+4] = x+y*bmpWidth;
            s_Indices[(x+y*(bmpWidth-1))*6+5] = x+(y+1)*bmpWidth;
        }
	}
	if(FAILED(device->CreateIndexBuffer((bmpWidth-1)*(bmpHeight-1)*6*sizeof(short),
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIB, NULL)))
	{
		MessageBox(hWnd, "RendererDirectX fillIndices: Error while creating IndexBuffer", "Error", MB_OK);
	}
	VOID* p_Indices;
	if(FAILED(g_pIB->Lock(0, (bmpWidth-1)*(bmpHeight-1)*6*sizeof(short),
		(void**)&p_Indices, 0)))
	{
		MessageBox(hWnd, "RendererDirectX fillIndices: Error while trying to lock memory", "Error", MB_OK);
	} 
	else
	{
		memcpy(p_Indices, s_Indices, (bmpWidth-1)*(bmpHeight-1)*6*sizeof(short));
		g_pIB->Unlock();
	}
	delete [] s_Indices;
};
*/