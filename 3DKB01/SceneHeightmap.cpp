#include "SceneHeightmap.h"


SceneHeightmap::SceneHeightmap(void)
{
};


SceneHeightmap::~SceneHeightmap(void)
{

};

int SceneHeightmap::set_offset (void)
{
    std::ifstream f_DataFile;
    WORD offset = 0;
    short dummy;

    f_DataFile.open("heightmap.bmp", std::ios::binary);
    
    char* test = new char[256];

    for (int i = 0; i < 255; i++)
    {
        test[i] = f_DataFile.get();
    }

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
