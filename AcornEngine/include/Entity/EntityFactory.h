#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "Entity/Entity.h"
#include "Cube.h"

class EntityFactory
{
private:
	//std::unordered_map<std::string, 
public:
	EntityFactory() = default;
	~EntityFactory() = default;
	Entity* makeCube();
};

#endif // ENTITY_FACTORY_H