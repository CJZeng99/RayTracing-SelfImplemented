#pragma once
#ifndef _RAY_H_
#define _RAY_H_
#include "core.h"
////////////////////////////////////////////////////////////////////////////////

class Ray
{
private:

	glm::vec3 origin;
	glm::vec3 direction;
	
	//hit information
	bool hasHit;
	float hitTime;
	glm::vec3 hitNormal;
	glm::vec3 hitPoint;
	float hitDistance;

public:

	Ray(glm::vec3 origin, glm::vec3 direction);
	~Ray();

	glm::vec3 getOrigin();
	glm::vec3 getDirection();
	bool getHasHit();
	float getHitTime();
	glm::vec3 getHitNormal();
	glm::vec3 getHitPoint();
	float getHitDistance();

	void handleHit(float hitTime);
	void setHitTime(float val);
	void setOrigin(glm::vec3 val);
	void setDirection(glm::vec3 val);
	void setHasHit(bool val);
	void setHitNormal(glm::vec3 val);
	void setHitPoint(glm::vec3 val);
	void setHitDistance(float val);

};

////////////////////////////////////////////////////////////////////////////////

#endif
