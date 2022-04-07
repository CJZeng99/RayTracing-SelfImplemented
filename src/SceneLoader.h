#ifndef _SCENELOADER_H_
#define _SCENELOADER_H_


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include "Scene.h"
#include "Object.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Raytracer.h"
#include "core.h"

class SceneLoader
{
public:
	SceneLoader(Scene* scene);
	~SceneLoader();
	bool ReadVals(std::stringstream& s, const int numvals, float* values);
	void ReadFile(const char* filename);

private:
	Scene* scene;
	std::string outputFile;

	std::vector<glm::vec3> vectices;
	std::stack <mat4> transfstack;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 emission;
	float shininess;
};

#endif

