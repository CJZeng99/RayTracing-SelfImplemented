#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iostream>

#include "FreeImage.h"

class Camera
{
public:
	Camera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up);
	~Camera();

	static int w, h;
	static float fovy;
	static float zNear;
	static float zFar;
	std::string outputFile;

	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;
	glm::mat4 projectionMtx;
	unsigned char* pixels;

	void Perspective(float fovy, float aspect, float zNear, float zFar);
	void SaveScreenshot();
};

float Camera::zNear = 0.1f;
float Camera::zFar = 99.0f;
#endif

