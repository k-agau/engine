#include "Entity/EntityManager.h"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

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

bool EntityManager::updateWorld(ENTITY_TYPE Target, Event& e)
{

	if (Target == ENTITY_TYPE::CAMERA)
	{

		EventType eventType = e.GetEventType();

		if (eventType == EventType::KeyPressed)
		{
			KeyPressedEvent* myE = dynamic_cast<KeyPressedEvent*>(&e);
			
			if (myE) {

				switch (myE->getKeyCode()) {
				case Key::W: camera->MoveForward(); return true;

				case Key::A: camera->MoveLeft(); return true;

				case Key::S: camera->MoveBackward(); return true;

				case Key::D: camera->MoveRight(); return true;

				case Key::J: {
					if (demo != 1) addCubeToWorld(glm::vec3(0, 0, 0));
					else addCubeToWorld(glm::vec3(randomUint8_t(), randomUint8_t(), randomUint8_t()));
					return true;
				}

				case Key::K:addPlaneToWorld(glm::vec3(randomUint8_t(), randomUint8_t(), 0)); return true;

				case Key::Right: demo = (demo + 1) % 3; return true;

				case Key::M: 
				{
					//camera->setStartOrientation();
					//1. copy view, inv camR, 2. remove translation in camR. 3. inv camR glm::inv
					//4. tr *inCamR *scale
					glm::mat4 camR = updateView();
					camR[3][0], camR[3][1], camR[3][2]= 0;

					glm::vec3 dPos = camera->GetPosition();
					Plane* p = (Plane*) addPlaneToWorld(dPos)->content();
					p->transform = glm::inverse(camR);
					/*p->front = glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f));
					glm::vec3 opp = glm::normalize(glm::normalize( -1.0f * camera->Front));
					p->transform = glm::rotate(p->transform, glm::angle(opp, p->front), glm::normalize(glm::cross(p->front, opp)));
					p->front = opp;
					p->right = glm::normalize(glm::normalize(-1.0f * camera->Right));
					p->up = glm::normalize(glm::cross(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0, 1.0, 0.0)));
					p->cUp = camera->Up;
					p->cFront = camera->Front;
					p->transform = glm::rotate(p->transform, glm::angle(p->right, glm::vec3(0.0, 1.0, 0.0)), glm::vec3(0.0f, 0.0f, -1.0f));*/
					//p->transform = glm::lookAt( dPos, camera->GetPosition(), glm::vec3(0, 1, 0));
					//glm::vec3 translateTo;
					//translateTo.x = dPos[0] - p->transform[3][0];
					//translateTo.y = dPos[1] - p->transform[3][1];
					//translateTo.z = dPos[2] - p->transform[3][2];
					//p->transform = glm::translate(p->transform, translateTo);
					// tmp = glm::dot(opp, up) /
					//	(glm::length(opp) * glm::length(up));
					// angle = glm::acos(tmp);
					//p->transform = glm::rotate(p->transform, angle, oth);
					///*p->transform = glm::lookAt(camera->GetPosition(), camera->Front * 1.5f, glm::vec3(0, 1, 0));
					p->transform[3][0] = dPos[0];
					p->transform[3][1] = dPos[1];
					p->transform[3][2] = dPos[2];
					p->transform = glm::scale(p->transform, glm::vec3(2.0f));
					//p->transform[3].z *= -1.0f;
					//p->setPostion(glm::vec3(tmp[3][0], tmp[3][0], tmp[3][0]));
					// Take opp vector and (-1.0,0.0,0.0), get angle, roate along their cross?
					//p->calculateTransform();
					isMouseDown = false;
					return false;
				}
				case Key::T: test = !test; break;
				}

			}
			return false;

		}
		else if (eventType == EventType::MousePressed)
		{
			isMouseDown = true;
			return true;
		}
		else if (eventType == EventType::MouseReleased)
		{
			isMouseDown = false;
			return true;
		}
		else if (eventType == EventType::MouseMoved)
		{

			MouseMoveEvent* myE = dynamic_cast<MouseMoveEvent*>(&e);

			if (myE) {

				if (!isMouseDown)
				{
					std::cout << myE->GetX() << ", " << myE->GetY() << std::endl;
					camera->updateMousePositions(myE->GetX(), myE->GetY());
				}
				else
				{
					camera->changeYawAndPitch(myE->GetX(), myE->GetY());
				}
				return true;

			}
		}

	}
	else {

	}
	return false;
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
	std::uniform_real_distribution<> distr(-5,5);
	if (demo == 2) {
		std::uniform_real_distribution<> distr(-20, 20);
		std::cout << demo << std::endl;
		return distr(gen);
	}
	else {
		std::uniform_real_distribution<> distr(0, 5);
		return distr(gen);
	}
	return distr(gen);

	

}

EntityManager::~EntityManager()
{

}
