#include "SceneHeightmap.h"


SceneHeightmap::SceneHeightmap(void)
{
};


SceneHeightmap::SceneHeightmap(RendererInterface* argRenderer, std::string argHeightmap, ResourceTexture* argTexture)
{
	// Set default position and orientation of the heightmap.
	position = Vector(	50.0f, -50.0f, -50.0f);
	orientation = Vector(0.0f, 0.0f, 0.0f);

	// Save the renderer and texture for later use.
	texture = argTexture;
	renderer = argRenderer;

	// "Location/name.bmp" of the heightmap bitmap file are converted to a LPCSTR.
	// InitializeImensions will read the height, width and offset info from the bitmap file header.
	LPCTSTR bitmap = argHeightmap.c_str();
	initializeDimensions(bitmap);

	// Create the index and vertexbuffer for the heightmap.
	fillVertices(bitmap);
	fillIndices();
}

SceneHeightmap::~SceneHeightmap(void)
{

};

// render method is called by the scene inside the program loop so the sceneheightmap will use the renderer to draw itself.
void SceneHeightmap::render()
{
	// Set the texture that was stored when the constructor was called.
	renderer->setTexture(texture);

	// Set the stream source and give the correct name with which the vertexbuffer was stored earlier so it can be used by the renderer.
	renderer->setStreamSource("Terrain");

	// Set the correct FvF type.
	renderer->setFvf();

	// Set the incdices while using the correct indexbuffer.
	renderer->setIndices("Terrain");

	// Move the matrix of the heightmap to the correct current orientation and position.
	renderer->moveMatrix(orientation, position);

	// Draw the heightmap.
	renderer->drawIndexedPrimitive(bmpWidth, bmpHeight);	
}

// fillIndices creates a indexbuffer for the heightmap inside the renderer.
void SceneHeightmap::fillIndices()
{
	// create an array of shorts and create a pointer to that array which can be passed on
	// to the renderer that will store the indexbuffer.
    short* s_Indices = new short[(bmpWidth-1)*(bmpHeight-1)*6];

    for (int x=0;x< bmpWidth-1;x++)    
	{
        for (int y=0; y< bmpHeight-1;y++)        
		{
            s_Indices[(x+y*(bmpWidth-1))*6+2] = x+y*bmpWidth;
            s_Indices[(x+y*(bmpWidth-1))*6+1] = (x+1)+y*bmpWidth;
            s_Indices[(x+y*(bmpWidth-1))*6] = (x+1)+(y+1)*bmpWidth;

            s_Indices[(x+y*(bmpWidth-1))*6+3] = (x+1)+(y+1)*bmpWidth;
            s_Indices[(x+y*(bmpWidth-1))*6+4] = x+y*bmpWidth;
            s_Indices[(x+y*(bmpWidth-1))*6+5] = x+(y+1)*bmpWidth;
        }
    }

	// The amount is the size of the araay which is needed in the renderer for creating the indexbuffer.
	int amount = (bmpWidth-1)*(bmpHeight-1)*6;

	// The name used to store the indexbuffer under so it can be acquired later.
	std::string type = "Terrain";

	// Give the renderer the short array of indices so it can create and store the indexbuffer.
	renderer->createIndexBuffer(amount, type, s_Indices);

    delete [] s_Indices;
}

// fillVertices creates a vertexbuffer for the heightmap inside the renderer.
void SceneHeightmap::fillVertices(LPCSTR argFileName)
{
	// Change determines the part of the texture file that needs to be put on each square of terrain created
	// If the image where 16 pixels wide then 1/16th of the image will be placed on 1/16  part of the heightmap.
	float changeWidth	= 1.0f / (float)bmpWidth;
	float changeHeight	= 1.0f / (float)bmpHeight;
	// Coordinates of the texture image fU height and fV width
	float fU		= 0	- changeHeight;
	float fV		= 0	- changeWidth;	

	// Create a pointer to an array of customvertexes that can be passed on to the renderer to create the vertexbuffer.
    CUSTOMVERTEX *cv_Vertices = new CUSTOMVERTEX[bmpWidth*bmpHeight];

    std::ifstream f_DataFile;
    short unsigned int dummy;
    f_DataFile.open(argFileName, std::ios::binary);
    if (f_DataFile.is_open())
    {
		// Skip the headerinfo from the bitmap file (offset)
        for (int i = 0;i< (bmpOffset);i++)        
		{
            dummy = f_DataFile.get();
        }

		// read out the pixeldata and store it in the customvertex array.
        for (int x=0;x< bmpWidth;x++)       
		{
			fV = 0 - changeWidth;
            for (int y=0; y< bmpHeight;y++)            
			{
				int height = f_DataFile.get();
                height += f_DataFile.get();
                height += f_DataFile.get();
                height /= 8;
                cv_Vertices[y*bmpWidth + x].x	= -x;
                cv_Vertices[y*bmpWidth + x].y	= height;
                cv_Vertices[y*bmpWidth + x].z	= y;
				cv_Vertices[y*bmpWidth + x].fU = fU;
				cv_Vertices[y*bmpWidth + x].fV = fV;
				fV = fV - changeWidth;
            }
			fU = fU - changeHeight;				
        }
    }

    f_DataFile.close();

	// The amount is the size of the araay which is needed in the renderer for creating the vertexbuffer.
	int amount = bmpWidth*bmpHeight;

	// The name used to store the vertexbuffer under so it can be acquired later.
	std::string type = "Terrain";

	// Give the renderer the array of customvertices so it can create and store the vertexbuffer.
    renderer->createVertexBuffer(amount, type, cv_Vertices);

    delete [] cv_Vertices;
}

// Reads the offset from the bitmap header file and returns the offset as an integer.
int SceneHeightmap::set_offset (LPCSTR argFileName)
{
    std::ifstream f_DataFile;
    WORD offset = 0;
    short dummy;

    f_DataFile.open(argFileName, std::ios::binary);

	// skip the first 10 bits of the bitmap header to get to the offset.
    for (int i = 0; i < 10; i++)
    {
        dummy = f_DataFile.get();
    }

	// Store the 4 bits that match the offset into the dword offset.
	// Inside the bitmap it is stored as type char and has to be converted hence the *256.
    offset = f_DataFile.get();
    offset += f_DataFile.get()*256;
    offset += f_DataFile.get()*256*256;
    offset += f_DataFile.get()*256*256*256;

    f_DataFile.close();
    
   return offset;
};

// Reads the height from the bitmap header file and returns this as a long.
long SceneHeightmap::set_height (LPCSTR argFileName)
{
    std::ifstream f_DataFile;
    long HEIGHT = 0;
    short dummy;

    f_DataFile.open(argFileName, std::ios::binary);

    if (f_DataFile.is_open())
    {
        // Skip the first 22 bits of the bitmap header to get to the height of the bitmap file.
		for (int i = 0; i < 22; i++)
        {
            dummy = f_DataFile.get();
        }
		// Store the 4 bits that match the offset into the int Height.
		// Inside the bitmap it is stored as type char and has to be converted hence the *256.
        HEIGHT = f_DataFile.get();
        HEIGHT += f_DataFile.get()*256;
        HEIGHT += f_DataFile.get()*256*256;
        HEIGHT += f_DataFile.get()*256*256*256;

        f_DataFile.close();
    }
    return HEIGHT;
};

// Reads the width from the bitmap header file and returns this as a long.
long SceneHeightmap::set_width (LPCSTR argFileName)
{
    std::ifstream f_DataFile;
    int WIDTH = 0;
    short dummy;

    f_DataFile.open(argFileName, std::ios::binary);

    if (f_DataFile.is_open())
    {
		// skip the first 18 bits of the bitmap header to get to the width of the heightmap.
        for (int i = 0; i < 18; i++)
        {
            dummy = f_DataFile.get();
        }

		// Store the 4 bits that match the width into the int WIDTH.
		// Inside the bitmap it is stored as type char and has to be converted hence the *256.
        WIDTH = f_DataFile.get();
        WIDTH += f_DataFile.get()*256;
        WIDTH += f_DataFile.get()*256*256;
        WIDTH += f_DataFile.get()*256*256*256;

        f_DataFile.close();
    }
    return WIDTH;
};


// initialize the offset and dimensions of the heightmap and store them in variables.
void SceneHeightmap::initializeDimensions(LPCSTR argFileName)
{
	bmpOffset = set_offset(argFileName);
	bmpWidth  = set_width(argFileName);
	bmpHeight = set_height(argFileName);
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

void SceneHeightmap::setPosition(Vector argPosition)
{
	position = argPosition;
};

Vector SceneHeightmap::getPosition()
{
	return position;
};

void SceneHeightmap::setOrientation(Vector argOrientation)
{
	orientation = argOrientation;
};

Vector SceneHeightmap::getOrientation()
{
	return orientation;
};

