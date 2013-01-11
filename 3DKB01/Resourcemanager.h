#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <d3dx9.h>
#include <d3d9.h>
#include <strsafe.h>
#include <mmsystem.h>
#include <fstream>
#include <map>
#include <string>

#include "ResourceModel.h"
#include "ResourceTexture.h"

class Resourcemanager
{
private:
	LPDIRECT3DDEVICE9 device;
	std::map<std::string, ResourceModel*> resourceModels;
	std::map<std::string, ResourceTexture*> resourceTextures;
public:
	Resourcemanager();
	~Resourcemanager(void);

	void setDevice(void*);

	HRESULT loadAllMeshes();
	HRESULT loadMesh(std::string);

	ResourceModel*		getResourceModel(std::string);
	ResourceTexture*	getResourceTexture(std::string);


//	HRESULT loadMaterials(LPDIRECT3DDEVICE9);
};

#endif __RESOURCEMANAGER_H__