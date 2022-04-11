#include "Grid.h"

bool Grid::checkIntersect(Ray* ray, bool checkShadow)
{
	//ray property
	float Ox = ray->getOrigin().x;
	float Oy = ray->getOrigin().y;
	float Oz = ray->getOrigin().z;
	float Dx = ray->getDirection().x;
	float Dy = ray->getDirection().y;
	float Dz = ray->getDirection().z;
	
	//box property
	float minX = min.x;
	float minY = min.y;
	float minZ = min.z;
	float maxX = max.x;
	float maxY = max.y;
	float maxZ = max.z;

	float tXMin = (minX - Ox) / Dx;
	float tXMax = (maxX - Ox) / Dx;
	if (tXMin > tXMax) {
		std::swap(tXMin, tXMax);
	}

	float tYMin = (minY - Oy) / Dy;
	float tYMax = (maxY - Oy) / Dy;
	if (tYMin > tYMax) {
		std::swap(tYMin, tYMax);
	}

	if ((tXMin > tYMax) || (tYMin > tXMax)) {
		return false;
	}
		
	if (tYMin > tXMin) {
		tXMin = tYMin;
	}
	if (tYMax < tXMax) {
		tXMax = tYMax;
	}

	float tZMin = (minZ - Oz) / Dz;
	float tZMax = (maxZ - Oz) / Dz;
	if (tZMin > tZMax) {
		std::swap(tZMin, tZMax);
	}
	if ((tXMin > tZMin) || (tZMin > tXMax)) {
		return false;
	}
	float currHitMin = INFINITY;
	for (auto child : this->children) {
		if (child->checkIntersect(ray)) {
			//hittime < hit min
			float currHitTime = ray->getHitTime();
			//std::cerr << currHitTime << "\n";
			if (currHitTime > 0 && currHitTime < currHitMin) {
				currHitMin = currHitTime;//update hit time

			}
		}
	}
	ray->handleHit(currHitMin);
	return true;
}