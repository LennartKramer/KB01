#include "Scenemanager.h"
#include <string>
#include <iostream>
#include <fstream>

Scenemanager::Scenemanager(void)
{
}
Scenemanager::~Scenemanager(void)
{
}

// Creates a scene
void Scenemanager::createScene(std::string argName, RendererInterface* argDirectX)
{
	Scene* scene = new Scene(argName, argDirectX);
	addScene(scene);
}

void Scenemanager::createSceneFromFile(std::string argLevelfile, RendererInterface* argDirectX, Resourcemanager* resources)
{
	createScene(argLevelfile, argDirectX);
	Scene* scene = getScene(argLevelfile);		
	std::string line;
	std::ifstream infile;
	infile.open (argLevelfile);
	getline(infile,line);
	while(line != "heightmap:") // skip lines until heightmap is found.
        {
	        getline(infile,line); // Saves the line in "line".
        }
			getline(infile,line); // Saves the line in "line".
			std::string heightmap = line;
			getline(infile,line); // Saves the line in "line".
			std::string terrain = line;
			scene->addTerrain(heightmap, resources->getResourceTexture(terrain));

	while(line != "skybox:") // skip lines until skybox is found.
        {
	        getline(infile,line); // Saves the line in "line".
        }
		getline(infile,line); // Saves the line in "line".
	while(line != "end") // load skybox from the lines until end is found
        {
			scene->addSkybox(resources->getResourceTexture(line));
			getline(infile,line); // Saves the line in "line".
        }
	while(line != "entities:") // skip lines until entities is found.
        {
	        getline(infile,line); // Saves the line in "line".
        }
		getline(infile,line); // Saves the line in "line".
	while(line != "end") // load entities from the lines until end is found
        {
			std::string buf; // Have a buffer string
			std::stringstream ss(line); // Insert the string into a stream

			std::vector<std::string> words; // Create vector to hold our words

			while (ss >> buf)
				words.push_back(buf);

			float positionX = (float)atof(words.at(3).c_str());
			float positionY = (float)atof(words.at(4).c_str());
			float positionZ = (float)atof(words.at(5).c_str());
			float orientationX = (float)atof(words.at(6).c_str());
			float orientationY = (float)atof(words.at(7).c_str());
			float orientationZ = (float)atof(words.at(8).c_str());

			Vector position = Vector(positionX, positionY, positionZ);
			Vector orientation = Vector(orientationX, orientationY, orientationZ);

			scene->addEntityModel(position, orientation, resources->getResourceModel(words.at(1)), resources->getResourceTexture(words.at(2)));

			 getline(infile,line); // Saves the line in "line".
        }
	scene->addEntityCamera();
}

// Adds scene to list
void Scenemanager::addScene(Scene* argScene)
{
	scenes.push_back(argScene);
}

// Get scene from list
Scene* Scenemanager::getScene(std::string argSceneName)
{
	std::list<Scene*>::iterator Iterator;
	for(Iterator = scenes.begin(); Iterator != scenes.end(); ++Iterator)
	{
		if((*Iterator)->getName() == argSceneName)
		{
			return (*Iterator);
		}
	}
	return NULL;
}

void Scenemanager::drawScene(Scene *argScene, POINT mouse, bool isMouseRPressed, int argKeyboardInput)
{
	//argScene->drawEntities(argTerSide,argTerFront,argTerUp);
	argScene->setView(mouse,isMouseRPressed); // set the view   ...(camera)
	argScene->renderScene(argKeyboardInput);
}


