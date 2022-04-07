#pragma once
#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include "Camera.h"
#include "Object.h"
#include "Ray.h"
////////////////////////////////////////////////////////////////////////////////

class Raytracer
{
	static int depth;
	static void tracer(Camera* cam, std::vector<Object*> objList);
	void getColor(Ray* ray, std::vector<Object*> objList);
};

////////////////////////////////////////////////////////////////////////////////

#endif
