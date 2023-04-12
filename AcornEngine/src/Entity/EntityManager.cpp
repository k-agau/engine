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
		auto transform = &newPlane->content()->getTransform();
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

				case Key::J: addCubeToWorld(glm::vec3(randomUint8_t(), randomUint8_t(), 0)); break;

				case Key::K: addPlaneToWorld(glm::vec3(randomUint8_t(), randomUint8_t(), 0)); break;

				case Key::B: addSphereToWorld(glm::vec3(randomUint8_t(), randomUint8_t(), 0), SPHERE_HIGH); break;
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

			// Handle collisions
			HandleCollisions(dt);

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

glm::vec3 EntityManager::projectUonV(const glm::vec3& u, const glm::vec3 v)
{
	glm::vec3 r;
	float scalar = glm::dot(u, v);
	r = v * scalar;
	return r;
}

glm::vec3 EntityManager::getNormal(const glm::vec3& u)
{
	return u / glm::length(u);
}

void EntityManager::HandleCollisions(float dt)
{
	auto objects = getWorldEntities();

	for (size_t i = 0; i < objects.size(); ++i)
	{
		for (size_t j = 0; j < objects.size() &&
			objects[i]->content()->getApplyCollision() &&
			(objects[i]->content()->type == SPHERE_HIGH ||
			objects[i]->content()->type == SPHERE_MID ||
			objects[i]->content()->type == SPHERE_LOW);
			 ++j)
		{
			if (!objects[j]->content()->getApplyCollision()) continue;
			if (i != j && objects[j]->content()->getApplyCollision())
			{
				if (objects[j]->content()->type & PLANE)
				{
					resolveSpherePlaneCollision(dynamic_cast<Sphere*>(objects[i]->content()), dynamic_cast<Plane*>(objects[j]->content()));
				}
				else if (objects[j]->content()->type & CUBE)
				{
					//resolveSphereCubeCollision(dynamic_cast<Sphere*>(objects[i]->content()), dynamic_cast<Cube*>(objects[j]->content()));
				}
				else if (objects[j]->content()->type & (SPHERE_HIGH | SPHERE_MID | SPHERE_LOW))
				{
					resolveSphereSphereCollision(dynamic_cast<Sphere*>(objects[i]->content()), dynamic_cast<Sphere*>(objects[j]->content()));
				}
				else
				{
					std::cout << "NOT YET IMPLEMENTED" << std::endl;
				}
			}
		}
	}
}

bool EntityManager::checkSpherePlaneCollision(Sphere* obj1, Plane* obj2)
{
	int rad1 = obj1->getRadius();

	auto point = obj1->getPosition();
	auto planePos = obj2->getPosition();

	auto sub = point - planePos;
	auto norm = obj2->getNormal();

	float dist = std::abs(glm::dot(sub, norm));

	if (dist > rad1) { // The sphere is not currently intersecting the plane
		return false;
	}

	// Additional checks: see if the sphere is still within bounds


	glm::vec3 projectedPoint = point - dist * norm;
	glm::quat planeRotation = obj2->getRotation();
	glm::vec3 rotatedProjectedPoint = planePos + glm::rotate(glm::inverse(planeRotation), projectedPoint - planePos);

	// Finite plane details
	float planeHalfWidth = obj2->xScale;
	float planeHalfHeight = obj2->yScale;

	// Check if the rotated projected point is within the finite plane
	return !(std::abs(rotatedProjectedPoint.x - planePos.x) > planeHalfWidth ||
		std::abs(rotatedProjectedPoint.y - planePos.y) > planeHalfHeight);
}

bool EntityManager::checkSphereSphereCollision(Sphere* obj1, Sphere* obj2)
{
	int rad1 = obj1->getRadius(), rad2 = obj2->getRadius();

	float dist = glm::length(obj1->getPosition() - obj2->getPosition());

	dist = std::sqrt(dist);

	return dist <= rad1 + rad2;
}

void EntityManager::resolveSpherePlaneCollision(Sphere* obj1, Plane* obj2)
{
	if (checkSpherePlaneCollision(obj1, obj2))
	{
		auto norm = obj2->getNormal();
		auto vel = obj1->getVelocity();

		glm::vec3 reflected = norm * (norm * vel) * 2.0f;

		/*glm::vec3* v = &obj1->getVelocity();
		*v -= reflected;*/

		auto v = &obj1->getVelocity();
		auto mag = glm::length(*v);

		*v = *v + norm * mag * .01f;

		auto x = 1 + 1;
	}
}

void EntityManager::resolveSphereCubeCollision(Sphere* obj1, Cube* obj2)
{

}

void EntityManager::resolveSphereSphereCollision(Sphere* obj1, Sphere* obj2)
{
	if (checkSphereSphereCollision(obj1, obj2))
	{
		auto pos1 = obj1->getPosition();
		auto pos2 = obj2->getPosition();

		glm::vec3 nv1(0.0f), nv2(0.0f); // New velocity vectors

		nv1 = obj1->getVelocity();
		nv1 += projectUonV(obj2->getVelocity(), pos2 - pos1);
		nv1 -= projectUonV(obj1->getVelocity(), pos1 - pos2);
		nv2 = obj2->getVelocity();
		nv2 += projectUonV(obj1->getVelocity(), pos2 - pos1);
		nv2 -= projectUonV(obj2->getVelocity(), pos1 - pos2);

		glm::vec3* v1 = &obj1->getVelocity();
		glm::vec3* v2 = &obj2->getVelocity();
		*v1 += nv1;
		*v2 += nv2;
	}
}

