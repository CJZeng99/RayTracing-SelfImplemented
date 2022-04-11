#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include "Camera.h"
#include "Light.h"
#include "Object.h"
#include "SceneLoader.h"
#include "Grid.h"
#include <vector>

class Scene
{
public:
	Scene(const char* inputFile);
	~Scene();

	Camera* cam;
	std::vector<Light*> lights;
	std::vector<Object*> grids;
	std::vector<Object*> objects;
	
	void InitGrid();
	void TakeScreenshots();
};

#endif

