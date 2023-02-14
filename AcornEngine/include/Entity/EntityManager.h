#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity/Entity.h"
#include <vector>

class EntityManager
{
private:
	EntityManager() = default;
	static EntityManager* inst;
	std::vector<Entity*> worldObjects;
public:
	~EntityManager();
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator= (const EntityManager&) = delete;

	static EntityManager* instance();
};

#endif // ENTITY_MANAGER_H