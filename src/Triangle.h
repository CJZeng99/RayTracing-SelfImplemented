#pragma once
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Object.h"
////////////////////////////////////////////////////////////////////////////////

class Triangle : Object
{
private:
	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;

public:
	Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	~Triangle();

	bool checkIntersect(Ray* ray, bool checkShadow = false);
	void computeMinMax();


};

////////////////////////////////////////////////////////////////////////////////

#endif
