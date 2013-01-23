#include "SceneHeightmap.h"


SceneHeightmap::SceneHeightmap(void)
{

};

SceneHeightmap::SceneHeightmap(RendererInterface* argRenderer, std::string argHeightmap, ResourceTexture* argTexture)
{
	position = Vector(0.0, 0.0, 0.0);
	texture = argTexture;
	renderer = argRenderer;

	LPCTSTR bitmap = argHeightmap.c_str();
	initializeDimensions(bitmap);

	fillVertices();
	fillIndices();
}

SceneHeightmap::~SceneHeightmap(void)
{

};

void SceneHeightmap::render(float argTerSide, float argTerFront, float argTerUp)
{
	
	
	float currentX = position.getX();
	float currentY = position.getY();
	float currentZ = position.getZ();

	float newPositionX = argTerSide + currentX;
	float newPositionY = argTerUp + currentY;
	float newPositionZ = argTerFront + currentZ;

	Vector newPosition = Vector(newPositionX, newPositionY, newPositionZ);

	setPosition(newPosition);

	renderer->setTexture(texture);

	renderer->setStreamSource("Terrain");
	renderer->setFvf("Terrain");
	renderer->setIndices("Terrain");

	renderer->drawIndexedPrimitive(position.getX(), position.getY(), position.getZ(), bmpWidth, bmpHeight);	
}

void SceneHeightmap::fillIndices()
{
	int WIDTH = bmpWidth;
	int HEIGHT = bmpHeight;

    short* s_Indices = new short[(WIDTH-1)*(HEIGHT-1)*6];

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

	int amount = (WIDTH-1)*(HEIGHT-1)*6;
	std::string type = "Terrain";

	renderer->createIndexBuffer(amount, type, s_Indices);

    delete [] s_Indices;
}

void SceneHeightmap::fillVertices()
{
	int offset = bmpOffset;
	int WIDTH = bmpWidth;
	int HEIGHT = bmpHeight;

	float change = 1.0f / (float)bmpWidth;
	float fU = 0- change;
	float fV = 0- change;	

    CUSTOMVERTEX *cv_Vertices = new CUSTOMVERTEX[WIDTH*WIDTH];

    std::ifstream f_DataFile;
    short unsigned int dummy;
    f_DataFile.open("heightmap.bmp", std::ios::binary);
    if (f_DataFile.is_open())
    {

        for (int i = 0;i< (offset);i++)        {
            dummy = f_DataFile.get();
        }

        for (int x=0;x< WIDTH;x++)        {
			fV = 0- change;
            for (int y=0; y< HEIGHT;y++)            {
				int height = f_DataFile.get();
                height += f_DataFile.get();
                height += f_DataFile.get();
                height /= 8;
                cv_Vertices[y*WIDTH + x].x = -x;
                cv_Vertices[y*WIDTH + x].y = height;
                cv_Vertices[y*WIDTH + x].z = y;
				cv_Vertices[y*WIDTH + x].fU = fU;
				cv_Vertices[y*WIDTH + x].fV = fV;
				fV = fV - change;
            }
				fU = fU - change;
				
        }
    }else{
        
    }

    f_DataFile.close();

	int amount = WIDTH*HEIGHT;
	std::string type = "Terrain";

    renderer->createVertexBuffer(amount, type, cv_Vertices);

    delete [] cv_Vertices;
}

int SceneHeightmap::set_offset (void)
{
    std::ifstream f_DataFile;
    WORD offset = 0;
    short dummy;

    f_DataFile.open("heightmap.bmp", std::ios::binary);

    for (int i = 0; i < 10; i++)
    {
        dummy = f_DataFile.get();
    }

    offset = f_DataFile.get();
    offset += f_DataFile.get()*256;
    offset += f_DataFile.get()*256*256;
    offset += f_DataFile.get()*256*256*256;

    f_DataFile.close();
    
   return offset;
};

long SceneHeightmap::set_height (void)
{
    std::ifstream f_DataFile;
    long HEIGHT = 0;
    short dummy;

    f_DataFile.open("heightmap.bmp", std::ios::binary);

    if (f_DataFile.is_open())
    {
        for (int i = 0; i < 22; i++)
        {
            dummy = f_DataFile.get();
        }

        HEIGHT = f_DataFile.get();
        HEIGHT += f_DataFile.get()*256;
        HEIGHT += f_DataFile.get()*256*256;
        HEIGHT += f_DataFile.get()*256*256*256;

        f_DataFile.close();
    }
    return HEIGHT;
};

long SceneHeightmap::set_width (void)
{
    std::ifstream f_DataFile;
    int WIDTH = 0;
    short dummy;

    f_DataFile.open("heightmap.bmp", std::ios::binary);

    if (f_DataFile.is_open())
    {

        for (int i = 0; i < 18; i++)
        {
            dummy = f_DataFile.get();
        }

        WIDTH = f_DataFile.get();
        WIDTH += f_DataFile.get()*256;
        WIDTH += f_DataFile.get()*256*256;
        WIDTH += f_DataFile.get()*256*256*256;

        f_DataFile.close();
    }
    return WIDTH;
};



bool SceneHeightmap::initializeDimensions(LPCSTR fileName)
{
	bmpOffset = set_offset();
	bmpWidth  = set_width();
	bmpHeight = set_height();

	return true;
};

int SceneHeightmap::getBitmapOffset(void)
{
	return bmpOffset;
};

int SceneHeightmap::getBitmapWidth(void)
{
	return bmpWidth;
};

int SceneHeightmap::getBitmapHeight(void)
{
	return bmpHeight;
};
