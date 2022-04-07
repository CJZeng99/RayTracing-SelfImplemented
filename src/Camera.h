#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	int w, h;

	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;
	glm::mat4 projection;

	unsigned char pixels[];

	void Perspective(float fovy, float aspect, float zNear, float zFar);
};

#endif

