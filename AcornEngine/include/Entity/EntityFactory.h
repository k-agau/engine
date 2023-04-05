#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "Entity/Entity.h"
#include "Cube.h"
#include "Plane.h"
#include "Sphere.h"

class EntityFactory
{
public:

	EntityFactory() = default;
	~EntityFactory() = default;

	Entity* makeCube(glm::vec3 wc);
	Entity* makePlane(glm::vec3 wc);
	Entity* makeSphere(glm::vec3 wc, unsigned int sector, unsigned int stacks, ENTITY_TYPE res);

};

#endif // ENTITY_FACTORY_H