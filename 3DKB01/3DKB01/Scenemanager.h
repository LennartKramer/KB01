#include "Scene.h"
#include "RendererDirectX.h"

class Scenemanager
{
private:
	Scene scene;

public:
	Scenemanager(void);
	Scenemanager(RendererDirectX* argDirectX);
	~Scenemanager(void);
};

