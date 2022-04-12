#include "Scene.h"

Scene::Scene(const char* inputFile)
{
	SceneLoader sl(this);
	sl.ReadFile(inputFile);
	std::cerr << "Finished loading input file " << inputFile << "\n";
	InitGrid();
	std::cerr << "Finished loading grid\n";
}

Scene::~Scene()
{
	for (auto light : lights)
		delete light;
	for (auto object : objects)
		delete object;
	delete cam;
}

void Scene::InitGrid()
{
	glm::vec3 gmax = glm::vec3(-INFINITY, -INFINITY, -INFINITY);
	glm::vec3 gmin = glm::vec3(INFINITY, INFINITY, INFINITY);
	for (auto obj : objects)
	{
		gmax.x = glm::max(gmax.x, obj->max.x);
		gmax.y = glm::max(gmax.y, obj->max.y);
		gmax.z = glm::max(gmax.z, obj->max.z);
		gmin.x = glm::min(gmin.x, obj->min.x);
		gmin.y = glm::min(gmin.y, obj->min.y);
		gmin.z = glm::min(gmin.z, obj->min.z);
	}
	glm::vec3 size = ((gmax - gmin) / Grid::side) + 1.0f;

	
	for (int xIdx = 0; xIdx < (int)size.x; xIdx++)
	{
		for (int yIdx = 0; yIdx < (int)size.y; yIdx++)
		{
			for (int zIdx = 0; zIdx < (int)size.z; zIdx++)
			{
				glm::vec3 thisMin = gmin + Grid::side * glm::vec3(xIdx, yIdx, zIdx);
				Grid* g = new Grid(thisMin);
				g->geoType = GeoType::grid;
				for (auto obj : objects)
				{
					if (Object::boxIntersect(g, obj))
						g->children.push_back(obj);
				}
				grids.push_back(g);
			}
		}
	}
	
}


void Scene::TakeScreenshots()
{
	Raytracer::tracer(cam, objects, lights);
	cam->SaveScreenshot();
}