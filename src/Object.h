#pragma once
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "core.h"
#include "Ray.h"
////////////////////////////////////////////////////////////////////////////////

enum class GeoType {sphere, tri};
class Object
{

public:
	virtual bool checkIntersect(Ray* ray, bool checkShadow = false) = 0;
	GeoType geoType;
	glm::vec3 min;
	glm::vec3 max;
	glm::mat4 model;
	glm::mat4 model_inverse;
	glm::mat4 model_transpose;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 emission;
	float shininess;

	static bool boxIntersect(Object* grid, Object* obj);
};

////////////////////////////////////////////////////////////////////////////////

#endif