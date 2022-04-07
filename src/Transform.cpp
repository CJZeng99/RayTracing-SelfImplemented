// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat4 Transform::rotate(const float degrees, const vec3& axis) 
{
    mat4 ret;
    ret = glm::rotate(mat4(), degrees, axis);
    return ret;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    mat4 ret;
    float d = glm::tan(90.0f - fovy / 2.0f);
    float d_asp = d / aspect;
    float A = -(zFar + zNear) / (zFar - zNear);
    float B = -(2.0f*zFar*zNear) / (zFar - zNear);
    ret = mat4(
        d_asp, 0.0f, 0.0f, 0.0f,
        0.0f, d, 0.0f, 0.0f,
        0.0f, 0.0f, A, -1.0f,
        0.0f, 0.0f, B, 0.0f
    );
    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    mat4 ret;
    ret = glm::scale(mat4(), vec3(sx, sy, sz));
    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    mat4 ret;
    ret = glm::translate(mat4(), vec3(tx, ty, tz));
    return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
