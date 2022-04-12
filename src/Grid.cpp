#include "Grid.h"

float Grid::side = 0.5f;
glm::vec3 Grid::gridMax = glm::vec3(- INFINITY, -INFINITY, -INFINITY);
glm::vec3 Grid::gridMin = glm::vec3( INFINITY, INFINITY, INFINITY);
glm::ivec3 Grid::gridRes = glm::ivec3(0,0,0);

Grid::Grid(const glm::vec3& min)
{
	this->min = min;
	this->max = min + side;
}

bool Grid::checkIntersect(Ray* ray, bool checkShadow)
{
	glm::vec3 origin = ray->getOrigin();
	glm::vec3 direction = ray->getDirection();

	float t_x_min = (min.x - origin.x) / direction.x;
	float t_x_max = (max.x - origin.x) / direction.x;
	if (t_x_min > t_x_max) {
		return false;
	}

	float t_y_min = (min.y - origin.y) / direction.y;
	float t_y_max = (max.y - origin.y) / direction.y;
	if (t_y_min > t_y_max) {
		return false;
	}

	if ((t_x_min > t_y_max) || (t_y_min > t_x_max)) {
		return false;
	}
		
	float t_xy_min = std::max(t_x_min, t_y_min);
	float t_xy_max = std::min(t_x_max, t_y_max);


	float t_z_min = (min.z - origin.z) / direction.z;
	float t_z_max = (max.z - origin.z) / direction.z;
	if (t_z_min > t_z_max) {
		return false;
	}

	if ((t_xy_min > t_z_max) || (t_z_min > t_xy_max)) {
		return false;
	}

	return true;
}