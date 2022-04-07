#include "Triangle.h"

////////////////////////////////////////////////////////////////////////////////
Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	this->geoType = GeoType::tri;
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
}
////////////////////////////////////////////////////////////////////////////////
Triangle::~Triangle()
{

}

////////////////////////////////////////////////////////////////////////////////
bool Triangle::checkIntersect(Ray * ray)
{
	//check intersection inside triangle
	glm::vec3 n = glm::cross(p2 - p1, p3 - p2);
	n = glm::normalize(n);
	
	//check if parallel
	if (glm::dot(n, ray->getDirection()) <= 0) {
		return false;
	}
	//calculating t 
	float t = (glm::dot(p1, n) - glm::dot(ray->getOrigin(), n)) / glm::dot(ray->getDirection(), n);
	
	//check if point inside 
	glm::vec3 guess = ray->guessPos(t);
	if (glm::dot(glm::cross(p2 - p1, guess - p1), n) > 0 &&
		glm::dot(glm::cross(p3 - p2, guess - p2), n) > 0 &&
		glm::dot(glm::cross(p1 - p3, guess - p3), n) > 0) {
		return false;
	}

	//handle hit time 
	ray->handleHit(t);
	return true;
}
////////////////////////////////////////////////////////////////////////////////
