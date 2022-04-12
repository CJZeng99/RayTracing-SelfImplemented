#pragma once
#ifndef _GRID_H_
#define _GRID_H_


#include "Object.h"

class Grid: public Object
{
public:
	static float side;
	static glm::vec3 gridMax;
	static glm::vec3 gridMin;
	static glm::ivec3 gridRes;
	std::vector<Object*> children;

	Grid(const glm::vec3& min);
	~Grid();

	bool checkIntersect(Ray* ray, bool checkShadow = true);
};

#endif

