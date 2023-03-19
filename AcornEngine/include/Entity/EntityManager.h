#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Camera.h"
#include "EntityFactory.h"
#include <vector>
#include <random>

class EntityManager
{
private:
	EntityManager();
	static EntityManager* inst;

	uint8_t randomUint8_t();
	const long max_rand = 1000000L;

	uint8_t lower_bound = 0;
	uint8_t upper_bound = 10;

	
	EntityFactory* factory;
public:

	~EntityManager();
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator= (const EntityManager&) = delete;

	std::vector<Entity*> worldObjects;
	Camera* camera;

	Entity* addCubeToWorld(glm::vec3 WorldCoords);
	Entity* addPlaneToWorld(glm::vec3 WorldCoords);
	glm::mat4 updateView();
	void updateWorld(Entity_Type Target, Event& e);
	const std::vector<Entity*> getWorldEntities() const;

	static EntityManager* instance();
};

#endif // ENTITY_MANAGER_H