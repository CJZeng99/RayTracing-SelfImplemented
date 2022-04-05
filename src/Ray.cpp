#include "Ray.h"

////////////////////////////////////////////////////////////////////////////////
Ray::Ray(glm::vec3 origin, glm::vec3 direction)
{
	this->origin = origin;
	this->direction = direction;
	this->hasHit = false;
	this->hitTime = 0.0;
	this->hitNormal = glm::vec3(0.0f);
	this->hitPoint = glm::vec3(0.0f);
	this->hitDistance = 0.0f;
}
////////////////////////////////////////////////////////////////////////////////
Ray::~Ray()
{

}
////////////////////////////////////////////////////////////////////////////////
void Ray::setOrigin(glm::vec3 val)
{
	this->origin = val;
}
////////////////////////////////////////////////////////////////////////////////
void Ray::setDirection(glm::vec3 val)
{
	this->direction = val;
}
////////////////////////////////////////////////////////////////////////////////
void Ray::setHasHit(bool val) 
{
	this->hasHit = val;
}
////////////////////////////////////////////////////////////////////////////////
void Ray::setHitNormal(glm::vec3 val)
{
	this->hitNormal = val;
}
////////////////////////////////////////////////////////////////////////////////
void Ray::setHitPoint(glm::vec3 val)
{
	this->hitPoint = val;
}
////////////////////////////////////////////////////////////////////////////////
void Ray::setHitDistance(float val)
{
	this->hitDistance = val;
}
////////////////////////////////////////////////////////////////////////////////
glm::vec3 Ray::getOrigin()
{
	return this->origin;
}
////////////////////////////////////////////////////////////////////////////////
glm::vec3 Ray::getDirection()
{
	return this->direction;
}
////////////////////////////////////////////////////////////////////////////////
bool Ray::getHasHit()
{
	return this->hasHit;
}
////////////////////////////////////////////////////////////////////////////////
float Ray::getHitTime()
{
	return this->hitTime;
}
////////////////////////////////////////////////////////////////////////////////
glm::vec3 Ray::getHitNormal()
{
	return this->hitNormal;
}
////////////////////////////////////////////////////////////////////////////////
glm::vec3 Ray::getHitPoint()
{
	return this->hitPoint;
}
////////////////////////////////////////////////////////////////////////////////
float Ray::getHitDistance()
{
	return this->hitDistance;
}
////////////////////////////////////////////////////////////////////////////////
