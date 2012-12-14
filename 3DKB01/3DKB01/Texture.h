#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "ResourceInterface.h"

class Texture: public ResourceInterface
{
public:
	Texture(void);
	~Texture(void);

	void loadModels(void);
	void loadTextures(void);
	LPD3DXBUFFER getLPD3DXBUFFER(void);
};

#endif _TEXTURE_H