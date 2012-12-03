#include "Scenemanager.h"
#include "Windowmanager.h"
#include "RendererDirectX.h"

class Kernel
{
private:
	RendererDirectX directX;
	Windowmanager windowmanager;
	Scenemanager scenemanager;
public:
	Kernel(void);
	~Kernel(void);
};

