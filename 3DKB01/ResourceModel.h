#ifndef __ResourceModel_H__
#define __ResourceModel_H__

#include <d3dx9.h>
#include <d3d9.h>

class ResourceModel
{
private:
	LPD3DXMESH*		g_pMesh;
public:
	ResourceModel(LPD3DXMESH*);
	~ResourceModel();

	LPD3DXMESH*		getMesh();
};

#endif