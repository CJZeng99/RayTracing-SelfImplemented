#include "Sphere.h"

////////////////////////////////////////////////////////////////////////////////
Sphere::Sphere(glm::vec3 center, float radius)
{
	this->geoType = GeoType::sphere;
	this->center = center;
	this->radius = radius;
}
////////////////////////////////////////////////////////////////////////////////
Sphere::~Sphere()
{
	
}

////////////////////////////////////////////////////////////////////////////////
bool Sphere::checkIntersect(Ray * ray) 
{
	//caculating intersection formual
	glm::vec3 P0 = ray->getOrigin();
	glm::vec3 P1 = ray->getDirection();
	glm::vec3 C = this->center;
	float r = this->radius;

	float a = glm::dot(P1 , P1);
	
	glm::vec3 diff = P0 - C;
	float b = 2 * dot(P1, diff);

	float temp = glm::dot(diff, diff);
	float c = temp - r * r;

	float discriminant = b * b - 4 * a * c + EPSILON;
	//no intersection
	if (discriminant < 0) {
		return false;
	}
	//when there is intersection
	float t1 = (-b + sqrt(discriminant)) / 2 * a;
	float t2 = (-b - sqrt(discriminant)) / 2 * a;
	
	//decide return value
	if(t2 > 0) {
		ray->handleHit(t2);
	}
	else if(t1 > 0){
		ray->handleHit(t1);
	}
	else {
		return false;
	}

	//seting ray hit normal
	ray->setHitNormal(glm::normalize(ray->getHitPoint() - this->center));
	return true;
	
}
////////////////////////////////////////////////////////////////////////////////
