#ifndef __Kernel_h__
#define __Kernel_h__

#include "Scenemanager.h"
#include "Windowmanager.h"
#include "RendererDirectX.h"
#include "Resourcemanager.h"
#include "Inputmanager.h"

class Kernel
{
private:
	RendererDirectX* directX;
	Windowmanager windowmanager;
	Scenemanager scenemanager;
	Resourcemanager resourcemanager;
	Inputmanager inputmanager;

public:
	Kernel(void);
	~Kernel(void);
};

#endif