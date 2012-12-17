#ifndef _MODEL_H
#define _MODEL_H

#include "ResourceInterface.h"

class Model: public ResourceInterface
{
public:
	Model(void);
	~Model(void);

	void loadModels(void);
	void loadTextures(void);
	LPD3DXBUFFER getLPD3DXBUFFER(void);
};

#endif _MODEL_H