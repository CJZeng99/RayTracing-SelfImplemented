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
	virtual bool checkIntersect(Ray * ray) = 0;
	GeoType geoType;
	glm::mat4 model;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 emission;
	float shininess;
};

////////////////////////////////////////////////////////////////////////////////

#endif