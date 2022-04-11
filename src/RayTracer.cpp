#pragma once
#include "Raytracer.h"

int Raytracer::depth = 5;

////////////////////////////////////////////////////////////////////////////////
void Raytracer::tracer(Camera* cam, const std::vector<Object *>& objList, const std::vector<Light*>& lightList)
{
	int width = Camera::w;
	int height = Camera::h;

	float halfwidth = width / 2;
	float halfheight = height / 2;

	//generating ray
	//for (int j = height / 4 - 1; j < height / 4; j++) {
	//	std::cerr << "\rRow Remaining: " << height - j << std::flush;
	//	for (int i = width / 4 - 1; i < width / 4; i++) {
	for (int j = 0; j < height; j++) {
		std::cerr << "\rRow Remaining: " << height - j << std::flush;
		for (int i = 0; i < width; i++) {
			//int progress = (int)((j * width + i) / (width * height) * 100);
			//std::cerr << "\rRayTracing Progress [" << std::string(progress, '#') << std::string(100-progress, ' ') << "]" << std::flush;

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
			glm::vec3 pixelColor = getColor(&currRay, objList, lightList, 0);
			//std::cerr << pixelColor.x << " , " << pixelColor.y << " , " << pixelColor.z << "\n";
			cam->pixels[3 * (j * width + i)] = unsigned char((int)(pixelColor.z * 255));
			cam->pixels[3 * (j * width + i) + 1] = unsigned char((int)(pixelColor.y * 255));
			cam->pixels[3 * (j * width + i) + 2] = unsigned char((int)(pixelColor.x * 255));
		}
	}

}
////////////////////////////////////////////////////////////////////////////////
glm::vec3 Raytracer::getColor(Ray* ray, const std::vector<Object*>& objList, const std::vector<Light*>& lightList, int currDepth)
{
	float currHitMin = INFINITY;
	glm::vec3 currHitPoint;
	glm::vec3 currHitNormal;
	Object* currHit;
	//loop through all objects
	for (int i = 0; i < objList.size(); i++) {
		Object* currObj = objList[i];
		//when intersect with object
		if (currObj->checkIntersect(ray)) {
			//hittime < hit min
			float currHitTime = ray->getHitTime();
			//std::cerr << currHitTime << "\n";
			if (currHitTime > 0 && currHitTime < currHitMin) {
				currHitMin = currHitTime;//update hit time
				currHit = currObj;
				currHitPoint = ray->getHitPoint();
				currHitNormal = ray->getHitNormal();
			}
		}
	}
	if (currHitMin < INFINITY)
	{
		//std::cerr << "Hit!\n";
		glm::vec3 color = currHit->ambient + currHit->emission;
		glm::vec3 diffuse_reflectance = glm::vec3(0.0f);
		glm::vec3 specular_reflectance = glm::vec3(0.0f);
		glm::vec3 hitPoint = currHitPoint + currHitNormal * glm::vec3(INTERSECT_EPSILON);

		if (glm::length(currHit->diffuse) > EPSILON || glm::length(currHit->specular) > EPSILON)
		{
			for (auto light : lightList)
			{
				// compute diffuse and specular
				if (light->type == LightType::point)
				{
					PointLight* point = (PointLight*)light;
					glm::vec3 L = glm::normalize(point->position - hitPoint);
					Ray shadowRay(hitPoint, L);
					for (auto obj : objList)
					{
						if (obj->checkIntersect(&shadowRay, true))
						{
							if (shadowRay.getHitTime() > 0 && shadowRay.getHitTime() < glm::length(point->position - hitPoint))
								return color;
						}
					}

					float r = glm::length(point->position - hitPoint);
					glm::vec3 r_vec = glm::vec3(1.0f, r, r * r);
					float attenFactor = glm::dot(Light::attenuation, r_vec);

					if (glm::length(currHit->diffuse) > EPSILON)
						diffuse_reflectance = currHit->diffuse * std::max(glm::dot(currHitNormal, L), 0.0f);

					if (glm::length(currHit->specular) > EPSILON)
					{
						glm::vec3 H = glm::normalize(L - ray->getDirection());
						specular_reflectance = currHit->specular * std::pow(std::max(glm::dot(currHitNormal, H), 0.0f), currHit->shininess);
					}

					color += light->color * (diffuse_reflectance + specular_reflectance) / attenFactor;
				}
				else if (light->type == LightType::directional)
				{
					DirectionalLight* directional = (DirectionalLight*)light;
					Ray shadowRay(hitPoint, directional->direction);
					for (auto obj : objList)
					{
						if (obj->checkIntersect(&shadowRay))
						{
							if (shadowRay.getHitTime() > 0 && shadowRay.getHitTime() < INFINITY)
								return color;
						}
					}
					if (glm::length(currHit->diffuse) > EPSILON)
						diffuse_reflectance = currHit->diffuse * std::max(glm::dot(ray->getHitNormal(), -normalize(directional->direction)), 0.0f);

					if (glm::length(currHit->specular) > EPSILON)
					{
						glm::vec3 H = glm::normalize(-normalize(directional->direction) - ray->getDirection());
						specular_reflectance = currHit->specular * std::pow(std::max(glm::dot(currHitNormal, H), 0.0f), currHit->shininess);
					}

					color += light->color * (diffuse_reflectance + specular_reflectance);
				}
			}

			if (glm::length(currHit->specular) > EPSILON && currDepth < depth)
			{
				currDepth++;
				glm::vec3 d = ray->getDirection();
				Ray traceRay(hitPoint, d - 2 * glm::dot(d, currHitNormal) * currHitNormal);
				color += currHit->specular * getColor(&traceRay, objList, lightList, currDepth);
			}
		}
		return color;
	}
	else
		return glm::vec3(0.0f);
}