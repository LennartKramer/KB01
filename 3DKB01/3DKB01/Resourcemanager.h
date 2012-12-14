#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include "ResourceInterface.h"

class Resourcemanager
{
private:
 	ResourceInterface* resourceInterface;
public:
	Resourcemanager(void);
	~Resourcemanager(void);

	void findTextures(void);
	void findModels(void);
	HRESULT retrieveTexturesAndModels(void);
};

#endif __RESOURCEMANAGER_H__