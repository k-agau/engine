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
	unsigned int uid = 0;

public:

	~EntityManager();
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator= (const EntityManager&) = delete;
	static EntityManager* instance();

	std::vector<Entity*> worldObjects;
	std::vector<std::pair<unsigned int, unsigned int>> sphereDimensions;
	Camera* camera;
	bool isMouseDown = false;

	//World Modifier Functions
	Entity* addCubeToWorld(glm::vec3 WorldCoords);
	Entity* addPlaneToWorld(glm::vec3 WorldCoords);
	Entity* addSphereToWorld(glm::vec3 WorldCoords, ENTITY_TYPE res);
	void removeEntity(int id);

	//Update Functions
	glm::mat4 updateView();
	void updateWorld(ENTITY_TYPE Target, Event& e);
	void worldStep();

	//Get
	const std::vector<Entity*> getWorldEntities() const;

	//Demo Helpers
	uint8_t randomUint8_t();
};

#endif // ENTITY_MANAGER_H