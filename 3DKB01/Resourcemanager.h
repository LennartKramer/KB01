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
	std::map<LPCTSTR, ResourceModel*> resourceModels;
	std::map<LPCTSTR, ResourceTexture*> resourceTextures;
public:
	Resourcemanager();
	~Resourcemanager(void);

	void setDevice(LPDIRECT3DDEVICE9);

	HRESULT loadAllMeshes();
	HRESULT loadMesh(LPCTSTR);

	ResourceModel*		getResourceModel(LPCTSTR);
	ResourceTexture*	getResourceTexture(LPCTSTR);


//	HRESULT loadMaterials(LPDIRECT3DDEVICE9);
};

#endif __RESOURCEMANAGER_H__