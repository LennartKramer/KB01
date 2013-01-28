#include "Scenemanager.h"

Scenemanager::Scenemanager()
{
}

Scenemanager::Scenemanager(Resourcemanager* argResourcemanager)
{
	resourcemanager = argResourcemanager;
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

// This will create the scene, load all the resource, and fill it with all the entities that are specified in the levelfile
void Scenemanager::createSceneFromFile(std::string argLevelfile, RendererInterface* argRenderer)
{
	HRESULT result;
	Logger::message("creating Scene from levelfile");
	createScene(argLevelfile, argRenderer); //create the scene
	Scene* scene = getScene(argLevelfile); // and save a pointer to it
	std::string line;
	std::ifstream infile;
	infile.open (argLevelfile);
	getline(infile,line); // Saves the first line in "line".
	while(line != "meshes:") // skip lines until meshes is found.
        {
	        getline(infile,line); // Saves the next line in "line".
        }
    getline(infile,line); // go to next line.
	Logger::message("loading meshes...");
	while(line != "end") // load meshes from the lines until end is found
        {
			result = resourcemanager->loadMesh("meshes/" + line);
			Logger::message(result, "	loading " + line);
			getline(infile, line); // Saves the line in "line".
        }
	Logger::message("...Done");
	while(line != "textures:") // skip lines until textures is found.
        {
	        getline(infile,line); // Saves the next line in "line".
        }
	getline(infile,line); // go to next line.
	Logger::message("loading meshes...");
	while(line != "end") // load textures from the lines until end is found
        {
			result = resourcemanager->loadTexture("textures/" + line);
			Logger::message(result, "	loading " + line);
			getline(infile,line); // Saves the next line in "line".
        }
	Logger::message("...Done");
	while(line != "heightmap:") // skip lines until heightmap is found.
        {
	        getline(infile,line); // Saves the next line in "line".
        }
			getline(infile,line); // Saves the next line in "line".
			Logger::message("loading terrain...");
			std::string heightmap = line;
			getline(infile,line); // Saves the next line in "line".
			std::string terrain = line;
			scene->addTerrain(heightmap, resourcemanager->getResourceTexture("textures/" + terrain));
			Logger::message("...Done");
	while(line != "skybox:") // skip lines until skybox is found.
        {
	        getline(infile,line); // Saves the next line in "line".
        }
		getline(infile,line); // go to next line.
		Logger::message("loading skybox...");
	while(line != "end") // load skybox from the lines until end is found
        {
			scene->addSkybox(resourcemanager->getResourceTexture("textures/" + line));
			getline(infile,line); // Saves the next line in "line".
        }
	Logger::message("...Done");
	while(line != "entities:") // skip lines until entities is found.
        {
	        getline(infile,line); // Saves the next line in "line".
        }
		getline(infile,line); // go to next line.
		Logger::message("creating entities...");
	while(line != "end") // load entities from the lines until end is found
        {
			std::string buf; // Have a buffer string
			std::stringstream ss(line); // Insert the string into a stream

			std::vector<std::string> words; // Create vector to hold our words

			while (ss >> buf) // save every word from the stringstream into the buffer
				words.push_back(buf); // save the string from the buffer in the vector

			float positionX = (float)atof(words.at(3).c_str());
			float positionY = (float)atof(words.at(4).c_str());
			float positionZ = (float)atof(words.at(5).c_str());
			float orientationX = (float)atof(words.at(6).c_str());
			float orientationY = (float)atof(words.at(7).c_str());
			float orientationZ = (float)atof(words.at(8).c_str());

			Vector position = Vector(positionX, positionY, positionZ);
			Vector orientation = Vector(orientationX, orientationY, orientationZ);

			scene->addEntityModel(position, orientation, resourcemanager->getResourceModel("meshes/" + words.at(1)), resourcemanager->getResourceTexture("textures/" + words.at(2)));

			 getline(infile,line); // Saves the line in "line".
        }
		Logger::message("...Done");
	    scene->addEntityCamera(argRenderer);
		Logger::message("Creating scene from levelfile completed!");
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


void Scenemanager::drawScene(Scene *argScene, POINT mouse, bool isMouseRPressed, Vector changedPosition, HWND hWnd)
{
	argScene->setView(mouse,isMouseRPressed); // set the view   ...(camera)
	argScene->renderScene(changedPosition, hWnd);
}


