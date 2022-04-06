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
	//TODO check intersection inside triangle
	glm::vec3 n = glm::cross(p2 - p1, p3 - p2);
	n = glm::normalize(n);
	//check if parallel
	if (abs(glm::dot(n, ray->getDirection()))< EPSILON) {
		return false;
	}
	
	
	float t = (glm::dot(p1, n) - glm::dot(ray->getOrigin(), n)) / glm::dot(ray->getDirection(), n);
	ray->handleHit(t);
	return true;
}
////////////////////////////////////////////////////////////////////////////////
