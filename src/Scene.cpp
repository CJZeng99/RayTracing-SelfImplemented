#include "Scene.h"

Scene::Scene(const char* inputFile)
{
	SceneLoader sl(this);
	sl.ReadFile(inputFile);
	std::cerr << "Finished loading imput file " << inputFile << "\n";
}

Scene::~Scene()
{
	for (auto light : lights)
		delete light;
	for (auto object : objects)
		delete object;
	delete cam;
}

void Scene::TakeScreenshots()
{

	cam->TakeScreenshot(objects);
	cam->SaveScreenshot();
}