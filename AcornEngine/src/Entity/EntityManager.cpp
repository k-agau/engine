#include "Entity/EntityManager.h"

EntityManager* EntityManager::inst = nullptr;

EntityManager::EntityManager() {

	factory = new EntityFactory();
	camera = new Camera();
}

Entity* EntityManager::addCubeToWorld(glm::vec3 WorldCoords)
{
	if (factory) {
		Entity* newCube = factory->makeCube(WorldCoords);
		worldObjects.push_back(newCube);
		return newCube;

	}
}

Entity* EntityManager::addPlaneToWorld(glm::vec3 WorldCoords)
{
	if (factory) {
		Entity* newPlane = factory->makePlane(WorldCoords);
		worldObjects.push_back(newPlane);
		return newPlane;

	}
}

glm::mat4 EntityManager::updateView()
{
	return camera->LookAt(camera->GetPosition() + camera->GetFront());
}

const std::vector<Entity*> EntityManager::getWorldEntities() const 
{

	return worldObjects;

}

void EntityManager::updateWorld(Entity_Type Target, Event& e) 
{

	if (Target == Entity_Type::CAMERA) 
	{

		if (e.GetEventType() == EventType::KeyPressed) 
		{
			KeyPressedEvent* myE = dynamic_cast<KeyPressedEvent*>(&e);
			
			if (myE) {

				switch (myE->getKeyCode()) 
				{

				case Key::W: camera->MoveForward(); break;

				case Key::A: camera->MoveLeft(); break;

				case Key::S: camera->MoveBackward(); break;

				case Key::D: camera->MoveRight(); break;

				case Key::H: addCubeToWorld(glm::vec3(randomUint8_t(), randomUint8_t(), 0)); break;

				case Key::J: addCubeToWorld(glm::vec3(randomUint8_t(), randomUint8_t(), 0)); break;

				case Key::V: addPlaneToWorld(glm::vec3(randomUint8_t(), randomUint8_t(), 0)); break;

				}

			}
			else { std::cout << "Somethin Fricked up" << std::endl; }

		}

		//std::cout << "CAMERA_UPDATE::MOVEMENT" << std::endl;

	}
	else {

	}

}

uint8_t EntityManager::randomUint8_t() {

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 5);

	return distr(gen);

}

EntityManager* EntityManager::instance()
{
	if (EntityManager::inst == nullptr)
	{
		inst = new EntityManager();
	}
	return inst;
}

EntityManager::~EntityManager()
{

}
