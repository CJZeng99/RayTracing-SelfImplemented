#include "Light.h"
////////////////////////////////////////////////////////////////////////////////
DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& color)
{
	this->direction = direction;
	this->color = color;
}
////////////////////////////////////////////////////////////////////////////////
DirectionalLight::~DirectionalLight()
{

}
////////////////////////////////////////////////////////////////////////////////
PointLight::PointLight(const glm::vec3& position, const glm::vec3& color)
{
	this->position = position;
	this->color = color;
}
////////////////////////////////////////////////////////////////////////////////
PointLight::~PointLight()
{

}
