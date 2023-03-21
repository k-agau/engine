#include "Entity/EntityFactory.h"

Entity* EntityFactory::makeCube(glm::vec3 wc)
{
	return new Entity(new Cube("tmp", wc[0], wc[1], wc[2]));
}

Entity* EntityFactory::makePlane(glm::vec3 wc)
{
	return new Entity(new Plane("tmp", wc[0], wc[1], wc[2]));
}
