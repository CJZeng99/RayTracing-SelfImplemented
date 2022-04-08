#include "Scene.h"

Scene::Scene(const char* inputFile)
{
	SceneLoader sl(this);
	sl.ReadFile(inputFile);
}