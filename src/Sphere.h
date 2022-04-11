#pragma once
#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Object.h"
////////////////////////////////////////////////////////////////////////////////

class Sphere : Object
{
private:
	glm::vec3 center;
	float radius;

public:

	Sphere(glm::vec3 center, float radius);
	~Sphere();

	bool checkIntersect(Ray* ray, bool checkShadow = false);
	glm::vec3 getCenter();
	glm::vec3 getRadius();

};

////////////////////////////////////////////////////////////////////////////////

#endif
