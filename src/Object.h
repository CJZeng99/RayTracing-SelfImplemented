#pragma once
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "core.h"
////////////////////////////////////////////////////////////////////////////////

enum class GeoType {sphere, tri};
class Object
{

public:

	Object();
	virtual ~Object() {};
	virtual bool checkIntersect(glm::vec3 origin, glm::vec3 dir, float& t) = 0;
	GeoType geoType;
	glm::mat4 model;
};

////////////////////////////////////////////////////////////////////////////////

#endif