#include "Sphere.h"

////////////////////////////////////////////////////////////////////////////////
Sphere::Sphere(glm::vec3 center, float radius)
{
	this->geoType = GeoType::sphere;
	this->center = center;
	this->radius = radius;

	this->ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	this->diffuse = glm::vec3(0.0f);
	this->specular = glm::vec3(0.0f);
	this->emission = glm::vec3(0.0f);
}
////////////////////////////////////////////////////////////////////////////////
Sphere::~Sphere()
{
	
}

////////////////////////////////////////////////////////////////////////////////
bool Sphere::checkIntersect(Ray* ray, bool checkShadow)
{
	//caculating intersection formual
	glm::vec3 P0 = glm::vec3(model_inverse * glm::vec4(ray->getOrigin(), 1.0f));
	glm::vec3 P1 = glm::normalize(glm::vec3(model_inverse * glm::vec4(ray->getDirection(), 0.0f)));
	glm::vec3 C = this->center;
	float r = this->radius;

	float a = glm::dot(P1 , P1);
	
	glm::vec3 diff = P0 - C;
	float b = 2 * dot(P1, diff);

	float temp = glm::dot(diff, diff);
	float c = temp - r * r;

	float discriminant = b * b - 4 * a * c;
	//no intersection
	if (discriminant < 0) {
		return false;
	}
	//when there is intersection
	float t1 = (-b + sqrt(discriminant)) / 2 * a;
	float t2 = (-b - sqrt(discriminant)) / 2 * a;
	glm::vec3 contactPoint;

	//decide return value
	if(t2 > 0) {
		contactPoint = glm::vec3(model * glm::vec4((P0 + P1 * t2), 1.0f));
		ray->handleHit(contactPoint);
		ray->setHitNormal(glm::normalize(glm::vec3(glm::transpose(model_inverse) * glm::vec4((P0 + P1 * t2 - this->center), 0.0f))));
	}
	else if(t1 > 0){
		contactPoint = glm::vec3(model * glm::vec4((P0 + P1 * t1), 1.0f));
		ray->handleHit(contactPoint);
		ray->setHitNormal(glm::normalize(glm::vec3(glm::transpose(model_inverse) * glm::vec4((P0 + P1 * t1 - this->center), 0.0f))));
	}
	else {
		return false;
	}

	//seting ray hit normal
	
	return true;
	
}
////////////////////////////////////////////////////////////////////////////////
