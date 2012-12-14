#include "Resourcemanager.h"


Resourcemanager::Resourcemanager(void)
{
	resourceInterface = new ResourceInterface();
};

Resourcemanager::~Resourcemanager(void)
{
	// Destructor. Leave this empty for now.
};

HRESULT Resourcemanager::retrieveTexturesAndModels(void)
{
	resourceInterface->loadModels();
	resourceInterface->loadTextures();

	resourceInterface->getLPD3DXBUFFER()->Release();
	return S_OK;
};
