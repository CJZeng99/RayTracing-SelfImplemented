// Transform header file to define the interface. 
// The class is all static for simplicity
// You need to implement left, up and lookAt
// Rotate is a helper function

// Include the helper glm library, including matrix transform extensions

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// glm provides vector, matrix classes like glsl
// Typedefs to make code more readable 

typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ; 
typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ; 
const float pi = 3.14159265f; // For portability across platforms


class Transform  
{
public:
	Transform();
	virtual ~Transform();
	static mat4 perspective(float fovy, float aspect, float zNear, float zFar);
    static mat4 rotate(const float degrees, const vec3& axis);
    static mat4 scale(const float &sx, const float &sy, const float &sz); 
    static mat4 translate(const float &tx, const float &ty, const float &tz);
    static vec3 upvector(const vec3 &up, const vec3 &zvec); 
};

