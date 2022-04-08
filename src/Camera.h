#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iostream>

#include "FreeImage.h"
#include "Object.h"
#include "RayTracer.h"

class Camera
{
public:
	Camera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up, float fovy, std::string outputFile);
	~Camera();

	static int w, h;
	static float zNear;
	static float zFar;
	
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;

	glm::vec3 right;
	glm::vec3 down;
	glm::vec3 front;

	float viewX;
	float viewY;
	float viewZ;
	
	float fovy;
	std::string outputFile;
	unsigned char* pixels;

	void TakeScreenshot(const std::vector<Object*>& objList);
	void SaveScreenshot();
};
#endif

