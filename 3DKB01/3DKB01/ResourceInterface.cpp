#include "ResourceInterface.h"

ResourceInterface::ResourceInterface(void)
{
	g_dwNumMaterials = 0L;
};

ResourceInterface::~ResourceInterface(void)
{
	// Interface class so do nothing...
};

void ResourceInterface::loadModels(void)
{
	// Interface class so do nothing...
};

void ResourceInterface::loadTextures(void)
{
	// Interface class so do nothing...
};

LPD3DXBUFFER ResourceInterface::getLPD3DXBUFFER(void)
{
	return pD3DXMtrlBuffer;
};