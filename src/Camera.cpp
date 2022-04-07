#include "Camera.h"

Camera::Camera() {}

Camera::~Camera() {}

void Camera::Perspective(float fovy, float aspect, float zNear, float zFar)
{
    
    float d = glm::tan(90.0f - fovy / 2.0f);
    float d_asp = d / aspect;
    float A = -(zFar + zNear) / (zFar - zNear);
    float B = -(2.0f * zFar * zNear) / (zFar - zNear);
    projection = glm::mat4(
        d_asp, 0.0f, 0.0f, 0.0f,
        0.0f, d, 0.0f, 0.0f,
        0.0f, 0.0f, A, -1.0f,
        0.0f, 0.0f, B, 0.0f
    );
}