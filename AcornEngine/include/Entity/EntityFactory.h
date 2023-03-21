#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "Entity/Entity.h"
#include "Cube.h"
#include "Plane.h"

class EntityFactory
{
private:
	//std::unordered_map<std::string, 
public:
	EntityFactory() = default;
	~EntityFactory() = default;
	Entity* makeCube(glm::vec3 wc);
	Entity* makePlane(glm::vec3 wc);
};

#endif // ENTITY_FACTORY_H