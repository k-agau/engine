#include "Entity/EntityFactory.h"

Entity* EntityFactory::makeCube(glm::vec3 wc)
{
	return new Entity(new Cube("tmp", wc));
}

Entity* EntityFactory::makePlane(glm::vec3 wc)
{
	return new Entity(new Plane("tmp", wc));
}

Entity* EntityFactory::makeSphere(glm::vec3 wc, unsigned int sector, unsigned int stacks, ENTITY_TYPE res)
{
	return new Entity(new Sphere("tmp", wc, sector, stacks, res));
}