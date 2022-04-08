#pragma once
#include "Raytracer.h"

int Raytracer::depth;

////////////////////////////////////////////////////////////////////////////////
void Raytracer::tracer(Camera* cam, std::vector<Object *> objList)
{
	int width = Camera::w;
	int height = Camera::h;

	float halfwidth = width / 2;
	float halfheight = height / 2;

	//generating ray
	for (int i = 0; i < width; i++) {
		for (int j = 0; i < height; j++) {
			
			//calculating ratios
			float xRatio = (i + 0.5 - halfwidth)/halfwidth;
			float yRatio = (j + 0.5 - halfheight)/halfheight;
			
			// ray direction
			glm::vec3 dir = cam->front * cam->viewZ +
				cam->down * cam->viewY * yRatio+
				cam->right * cam->viewX* xRatio;
			dir = glm::normalize(dir);
			
			//generating ray
			Ray currRay(cam->eye, dir);
			//get color 

		}
	}

}
////////////////////////////////////////////////////////////////////////////////
void Raytracer::getColor(Ray* ray, std::vector<Object*> objList) 
{
	float hit_min = FLT_MAX;
	float infinity = FLT_MAX;
	//loop through all objects
	for (int i = 0; i < objList.size(); i++) {
		Object* currObj = objList[i];
		//when intersect with object
		if (currObj->checkIntersect(ray)) {
			//hittime < hit min
			float currHitTime = ray->getHitTime();
			if (currHitTime < hit_min && currHitTime < INFINITY) {
				hit_min = ray->getHitTime();//update hit time
				//TODO update pixel color 
			}
		}
	}
}