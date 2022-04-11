#include "Triangle.h"

////////////////////////////////////////////////////////////////////////////////
Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	this->geoType = GeoType::tri;
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;

	p1 = glm::vec3(model * glm::vec4(this->p1, 1.0f));
	p2 = glm::vec3(model * glm::vec4(this->p2, 1.0f));
	p3 = glm::vec3(model * glm::vec4(this->p3, 1.0f));

	this->min.x = std::min(std::min(p1.x, p2.x), p3.x );
	this->min.y = std::min(std::min(p1.y, p2.y), p3.y );
	this->min.z = std::min(std::min(p1.z, p2.z), p3.z );
	this->max.x = std::max(std::max(p1.x, p2.x), p3.x );
	this->max.y = std::max(std::max(p1.y, p2.y), p3.y );
	this->max.z = std::max(std::max(p1.z, p2.z), p3.z );

	this->ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	this->diffuse = glm::vec3(0.0f);
	this->specular = glm::vec3(0.0f);
	this->emission = glm::vec3(0.0f);
}
////////////////////////////////////////////////////////////////////////////////
Triangle::~Triangle()
{

}

////////////////////////////////////////////////////////////////////////////////
bool Triangle::checkIntersect(Ray * ray, bool checkShadow)
{
	glm::vec3 p1 = glm::vec3(model * glm::vec4(this->p1, 1.0f));
	glm::vec3 p2 = glm::vec3(model * glm::vec4(this->p2, 1.0f));
	glm::vec3 p3 = glm::vec3(model * glm::vec4(this->p3, 1.0f));

	//check intersection inside triangle
	glm::vec3 n = glm::cross(p2 - p1, p3 - p1);
	n = glm::normalize(n);

	glm::vec3 rayPos = ray->getOrigin();
	glm::vec3 rayDir = ray->getDirection();


	//check if parallel
	if (glm::dot(n, rayDir) > -EPSILON && !checkShadow) {
		return false;
	}
	//std::cerr << "DOT: " << glm::dot(rayDir, n) << "\n";
	float t = (glm::dot(p1, n) - glm::dot(rayPos, n)) / glm::dot(rayDir, n);
	
	//check if point inside 
	glm::vec3 guess = ray->guessPos(t);
	if (glm::dot(glm::cross(p2 - p1, guess - p1), n) < 0 ||
		glm::dot(glm::cross(p3 - p2, guess - p2), n) < 0 ||
		glm::dot(glm::cross(p1 - p3, guess - p3), n) < 0) {
		return false;
	}

	//handle hit time 
	ray->handleHit(t);
	ray->setHitNormal(n);
	return true;
}
////////////////////////////////////////////////////////////////////////////////
