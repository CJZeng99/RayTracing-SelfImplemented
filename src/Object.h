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

	static bool boxIntersect(Object* obj1, Object* obj2) {
		return (obj1->min.x <= obj2->max.x && obj1->max.x >= obj2->min.x) &&
			(obj1->min.y <= obj2->max.y && obj1->max.y >= obj2->min.y) &&
			(obj1->min.z <= obj2->max.z && obj1->max.z >= obj2->min.z);
	}
};

////////////////////////////////////////////////////////////////////////////////

#endif