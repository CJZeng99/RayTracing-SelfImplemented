#pragma once
#include <glm/glm.hpp>

enum class LightType{directional, point};

class Light
{
public:
	LightType type;
	glm::vec3 ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	float attenuation[3] = { 1.0f, 0.0f, 0.0f };
};

class DirectionalLight : public Light
{
public:
	glm::vec3 direction;
	DirectionalLight(const glm::vec3& direction, const glm::vec3& );
};

class PointLight : public Light
{
public:
	glm::vec3 position;
	PointLight(const glm::vec3& position);
};

