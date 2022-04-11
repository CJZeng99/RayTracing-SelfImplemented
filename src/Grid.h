
#include "Object.h"

class Grid : public Object
{
	static float side;
	glm::vec3 max;
	glm::vec3 min;
	std::vector<Object*> children;

	Grid(const glm::vec3& min);
	~Grid();

	bool checkIntersect(Ray* ray, bool checkShadow = true);
};

