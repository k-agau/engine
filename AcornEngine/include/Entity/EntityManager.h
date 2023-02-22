#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Core/Camera.h"
#include "Entity/EntityFactory.h"
#include <vector>

class EntityManager
{
private:
	EntityManager();
	static EntityManager* inst;
	
	EntityFactory* factory;
public:

	~EntityManager();
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator= (const EntityManager&) = delete;

	std::vector<Entity*> worldObjects;
	Camera* camera;

	Entity* addCubeToWorld();
	glm::mat4 updateView();
	void updateWorld(Entity_Type Target, Event& e);
	const std::vector<Entity*> getWorldEntities() const;

	static EntityManager* instance();
};

#endif // ENTITY_MANAGER_H