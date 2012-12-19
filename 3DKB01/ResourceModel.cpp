#include "ResourceModel.h"


ResourceModel::ResourceModel(LPD3DXMESH* argMesh)
{
	g_pMesh = argMesh;
}

ResourceModel::~ResourceModel()
{
	
}

LPD3DXMESH* ResourceModel::getMesh()
{
	return g_pMesh;
}