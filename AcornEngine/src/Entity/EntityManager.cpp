#include "Entity/EntityManager.h"

#include "Layers/LayerStack.h"
#include "Layers/MenuLayer.h"

EntityManager* EntityManager::inst = nullptr;

EntityManager::EntityManager() {

	factory = new EntityFactory();
	camera = new Camera();
}

Entity* EntityManager::addCubeToWorld()
{
	if (factory) {

		Entity* newCube = factory->makeCube();
		worldObjects.push_back(newCube);
		return newCube;
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

				switch (myE->getKeyCode()) {
				case Key::W: camera->MoveForward(); break;

				case Key::A: camera->MoveLeft(); break;

				case Key::S: camera->MoveBackward(); break;

				case Key::D: camera->MoveRight(); break;
				
				case Key::B: LayerStack::instance()->pushOverlay(new MenuLayer());  break;
				}

			}
			else { std::cout << "Somethin Fricked up" << std::endl; }

		}

		std::cout << "CAMERA_UPDATE::MOVEMENT" << std::endl;

	}
	else {

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

EntityManager::~EntityManager()
{

}
