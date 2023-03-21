#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Core/Camera.h"
#include "Entity/EntityFactory.h"
#include <random>
#include <vector>

class EntityManager
{
private:
	EntityManager();
	static EntityManager* inst;
	
	EntityFactory* factory;

	glm::vec3 gravity = glm::vec3(0, -9.81, 0);
public:

	~EntityManager();
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator= (const EntityManager&) = delete;

	std::vector<Entity*> worldObjects;
	Camera* camera;

	Entity* addCubeToWorld(glm::vec3 WorldCoords);
	Entity* addPlaneToWorld(glm::vec3 WorldCoords);
	glm::mat4 updateView();
	void updateWorld(ENTITY_TYPE Target, Event& e);
	void worldStep();
	uint8_t randomUint8_t();
	const std::vector<Entity*> getWorldEntities() const;

	static EntityManager* instance();
};

#endif // ENTITY_MANAGER_H