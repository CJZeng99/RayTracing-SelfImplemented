#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include "Camera.h"
#include "Object.h"
#include "Transform.h"

#include <vector>

class Scene
{
public:
	Scene();
	~Scene();

	Transform* trans;
	Camera* cam;
	std::vector<glm::vec3> vertices;
	std::vector<Object*> objects;
};

#endif

