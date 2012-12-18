#include "SceneHeightmap.h"


SceneHeightmap::SceneHeightmap(void)
{

};


SceneHeightmap::~SceneHeightmap(void)
{

};

bool SceneHeightmap::initializeDimensions(LPCSTR fileName)
{
	std::ifstream f_DataFile;
	
	f_DataFile.open(fileName, std::ios::binary);
	
	if(f_DataFile.get() != NULL)
	{
		bmpOffset = f_DataFile.get();
		bmpOffset += f_DataFile.get()*256;
		bmpOffset += f_DataFile.get()*256*256;
		bmpOffset += f_DataFile.get()*256*256*256;
		std::cout << "Bitmap offset: " << bmpOffset << std::endl;

		bmpWidth = f_DataFile.get();
		bmpWidth += f_DataFile.get()*256;
		bmpWidth += f_DataFile.get()*256*256;
		bmpWidth += f_DataFile.get()*256*256*256;
		std::cout << "Bitmap width: " << bmpWidth << std::endl;

		bmpHeight = f_DataFile.get();
		bmpHeight += f_DataFile.get()*256;
		bmpHeight += f_DataFile.get()*256*256;
		bmpHeight += f_DataFile.get()*256*256*256;
		std::cout << "Bitmap height: " << bmpHeight << std::endl;

		f_DataFile.close();
	}
	else
		throw(TEXT("SceneHeightmap initializeDimensions: Failed to open bitmap file!"));
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
