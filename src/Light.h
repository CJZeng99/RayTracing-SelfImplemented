#pragma once
#include <glm/glm.hpp>

enum class LightType{directional, point};

class Light
{
public:
	LightType type;
	glm::vec3 color;
	static glm::vec3 attenuation;
};

class DirectionalLight : public Light
{
public:
	
	glm::vec3 direction;
	DirectionalLight(const glm::vec3& direction, const glm::vec3& color);
	~DirectionalLight();
};

class PointLight : public Light
{
public:
	
	glm::vec3 position;
	PointLight(const glm::vec3& position, const glm::vec3& color);
	~PointLight();
};

