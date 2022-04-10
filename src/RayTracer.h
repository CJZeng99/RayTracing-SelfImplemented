#pragma once
#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include "Camera.h"
#include "Object.h"
#include "Light.h"
#include "Ray.h"
////////////////////////////////////////////////////////////////////////////////
class Camera;
class Raytracer
{
public:
	static int depth;
	static void tracer(Camera* cam, const std::vector<Object*>& objList, const std::vector<Light*>& lightList);
	static glm::vec3 getColor(Ray* ray, const std::vector<Object*>& objList, const std::vector<Light*>& lightList);
};

////////////////////////////////////////////////////////////////////////////////

#endif
