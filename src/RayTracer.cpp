#pragma once
#include "Raytracer.h"

int Raytracer::depth;

////////////////////////////////////////////////////////////////////////////////
void Raytracer::tracer(Camera* cam, const std::vector<Object *>& objList)
{
	int width = Camera::w;
	int height = Camera::h;

	float halfwidth = width / 2;
	float halfheight = height / 2;

	//generating ray
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			
			//calculating ratios
			float xRatio = (i + 0.5 - halfwidth)/halfwidth;
			float yRatio = (j + 0.5 - halfheight)/halfheight;
			
			// ray direction
			glm::vec3 dir = cam->front * cam->viewZ +
				cam->down * cam->viewY * yRatio+
				cam->right * cam->viewX * xRatio;
			dir = glm::normalize(dir);

			//generating ray
			Ray currRay(cam->eye, dir);
			//get color 
			glm::vec3 pixelColor = getColor(&currRay, objList);
			//std::cerr << pixelColor.x << " , " << pixelColor.y << " , " << pixelColor.z << "\n";
			cam->pixels[3 * (j * width + i)] = unsigned char((int)(pixelColor.z * 255));
			cam->pixels[3 * (j * width + i) + 1] = unsigned char((int)(pixelColor.y * 255));
			cam->pixels[3 * (j * width + i) + 2] = unsigned char((int)(pixelColor.x * 255));
		}
	}

}
////////////////////////////////////////////////////////////////////////////////
glm::vec3 Raytracer::getColor(Ray* ray, const std::vector<Object*>& objList)
{
	float hit_min = INFINITY;
	//loop through all objects
	for (int i = 0; i < objList.size(); i++) {
		Object* currObj = objList[i];
		//when intersect with object
		if (currObj->checkIntersect(ray)) {
			//hittime < hit min
			float currHitTime = ray->getHitTime();
			//std::cerr << currHitTime << "\n";
			if (currHitTime > 0 && currHitTime < hit_min) {
				hit_min = currHitTime;//update hit time
			}
		}
	}
	if (hit_min < INFINITY)
	{
		//std::cerr << "Hit!\n";
		return Light::ambient;
	}
	else
		return glm::vec3(0.0f);
}