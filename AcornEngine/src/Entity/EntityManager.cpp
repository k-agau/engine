#include "Entity/EntityManager.h"

extern float dt;

EntityManager* EntityManager::inst = nullptr;

EntityManager::EntityManager() {

	factory = new EntityFactory();
	camera = new Camera();
}

Entity* EntityManager::addCubeToWorld(glm::vec3 WorldCoords)
{
	if (factory) 
	{

		Entity* newCube = factory->makeCube(WorldCoords);
		worldObjects.push_back(newCube);
		return newCube;

	}
}

Entity* EntityManager::addPlaneToWorld(glm::vec3 WorldCoords)
{
	if (factory) 
	{

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

void EntityManager::updateWorld(ENTITY_TYPE Target, Event& e)
{

	if (Target == ENTITY_TYPE::CAMERA)
	{

		EventType eventType = e.GetEventType();

		if (eventType == EventType::KeyPressed)
		{
			KeyPressedEvent* myE = dynamic_cast<KeyPressedEvent*>(&e);
			
			if (myE) {

				switch (myE->getKeyCode()) {
				case Key::W: camera->MoveForward(); break;

				case Key::A: camera->MoveLeft(); break;

				case Key::S: camera->MoveBackward(); break;

				case Key::D: camera->MoveRight(); break;

				case Key::J:addCubeToWorld(glm::vec3(randomUint8_t(), randomUint8_t(), 0)); break;

				case Key::K:addPlaneToWorld(glm::vec3(randomUint8_t(), randomUint8_t(), 0)); break;
				}

			}
			else { std::cout << "Somethin Fricked up" << std::endl; }

		}
		else if (eventType == EventType::MousePressed)
		{
			isMouseDown = true;
		}
		else if (eventType == EventType::MouseReleased)
		{
			isMouseDown = false;
		}
		else if (eventType == EventType::MouseMoved)
		{

			MouseMoveEvent* myE = dynamic_cast<MouseMoveEvent*>(&e);

			if (myE) {

				if (!isMouseDown)
				{
					camera->updateMousePositions(myE->GetX(), myE->GetY());
				}
				else
				{
					camera->changeCameraYawAndPitch(myE->GetX(), myE->GetY());
				}

			}
		}

	}
	else {

	}

}

void EntityManager::worldStep()
{
	for (auto obj : worldObjects)
	{
		glm::vec3* f = &obj->content()->force;
		glm::vec3* p = &obj->content()->position;
		glm::vec3* v = &obj->content()->velocity;
		float* m = &obj->content()->mass;

		//apply gravity
		*f += *m * gravity;
		*v += *f / *m * dt;
		*p += *v * dt;

		//reset force
		*f = glm::vec3(0, 0, 0);

	}
}

EntityManager* EntityManager::instance()
{
	if (EntityManager::inst == nullptr)
	{
		inst = new EntityManager();
	}
	return inst;
}

uint8_t EntityManager::randomUint8_t() 
{

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 5);

	return distr(gen);

}

EntityManager::~EntityManager()
{

}
