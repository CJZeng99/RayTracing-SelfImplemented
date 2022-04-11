
#include "Object.h"

class Grid : public Object
{
public:
	static float side;
	std::vector<Object*> children;

	Grid(const glm::vec3& min);
	~Grid();

	bool checkIntersect(Ray* ray, bool checkShadow = true);
};

