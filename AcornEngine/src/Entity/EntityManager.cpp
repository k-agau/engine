#include "Entity/EntityManager.h"

extern float dt;

EntityManager* EntityManager::inst = nullptr;

EntityManager::EntityManager() {

	factory = new EntityFactory();
	camera = new Camera();

	sphereDimensions.push_back(std::pair(10, 10)); //Low  Dimensional Sphere
	sphereDimensions.push_back(std::pair(30, 30)); //Mid  Dimensional Sphere
	sphereDimensions.push_back(std::pair(70, 70)); //High Dimensional Sphere

}

Entity* EntityManager::addCubeToWorld(glm::vec3 WorldCoords)
{
	if (factory) 
	{

		Entity* newCube = factory->makeCube(WorldCoords);
		newCube->content()->setID(++uid);
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
		newPlane->content()->setID(++uid);
		return newPlane;

	}
}

Entity* EntityManager::addSphereToWorld(glm::vec3 WorldCoords, ENTITY_TYPE res)
{
	if (factory)
	{

		Entity* newSphere = factory->makeSphere(
			WorldCoords,
			sphereDimensions[res-2].first,		//the offset from the enum position is 2
			sphereDimensions[res-2].second,	
			res
		);
		newSphere->content()->setID(++uid);
		worldObjects.push_back(newSphere);
		return newSphere;

	}
}

void EntityManager::removeEntity(int id)
{
	for (auto it = worldObjects.begin(); it < worldObjects.end(); ++it)
	{
		if ((*it)->content()->getID() == id)
		{
			(*it)->content()->~EntityImpl();
			(*it)->~Entity();
			worldObjects.erase(it);
			return;
		}
	}

	std::cout << "ENTITY_MANAGER::ENTITY WAS NOT FOUND AND ERASED" << std::endl;

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
	for (auto objPtr : worldObjects)
	{
		auto obj = objPtr->content();

		if (obj->getApplyPhysics())
		{

			//get object values
			glm::vec3* f = &obj->getForce();
			glm::vec3* p = &obj->getPosition();
			glm::vec3* v = &obj->getVelocity();
			float	   m =  obj->getMass();

			//apply gravity
			*f += m * gravity;
			*v += *f / m * dt;
			*p += *v * dt;

			//reset force
			*f = glm::vec3(0, 0, 0);

		}

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
