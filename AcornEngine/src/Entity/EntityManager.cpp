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
	collideSphere = false;
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

bool EntityManager::updateWorld(ENTITY_TYPE Target, Event& e)
{

	EventType eventType = e.GetEventType();

	if (Target == ENTITY_TYPE::CAMERA)
	{

		if (eventType == EventType::KeyPressed)
		{
			KeyPressedEvent* myE = dynamic_cast<KeyPressedEvent*>(&e);
			
			if (myE) {
				switch (myE->getKeyCode()) {
				case Key::W: camera->MoveForward(); return true;

				case Key::A: camera->MoveLeft(); return true;

				case Key::S: camera->MoveBackward(); return true;

				case Key::D: camera->MoveRight(); return true;

				case Key::Right: demo = (demo + 1) % 3; return true;

				case Key::T: test = !test; break;
        
				case Key::J: addCubeToWorld(glm::vec3(randomUint8_t(), randomUint8_t(), 0)); return true;

				case Key::K: addPlaneToWorld(glm::vec3(randomUint8_t(), randomUint8_t(), 0)); return true;

				case Key::B:{

						auto tmp = addSphereToWorld(glm::vec3(randomUint8_t(), randomUint8_t(), 0), SPHERE_HIGH); return true;
						tmp->content()->setApplyCollision(true);
						color = ++color % 8;
						COLORS c = static_cast<COLORS>(color);
						tmp->content()->setColor(c);
				}
				case Key::L: collideSphere = !collideSphere; return true;
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

		if (eventType == EventType::Scale)
		{
			ScaleEvent* myE = dynamic_cast<ScaleEvent*>(&e);

			if (myE)
			{

				for (auto i : worldObjects)
				{
					if (i->content()->getID() == myE->uid)
					{
						auto a = (Cube*)i->content();
						if (myE->getMod() == INC)
						{
							a->scale[0] += 1.5f;
							a->scale[1] += 1.5f;
							a->scale[2] += 1.5f;
						}
						else
						{
							a->scale[0] -= 1.5f;
							a->scale[1] -= 1.5f;
							a->scale[2] -= 1.5f;
						}

						a->setTransform(glm::scale(a->getTransform(), a->scale) );
						return true;
					}
				}
			}
		}
		if (eventType == EventType::Rotate)
		{
			RotateEvent* myE = dynamic_cast<RotateEvent*>(&e);

			if (myE)
			{

				for (auto i : worldObjects)
				{
					if (i->content()->getID() == myE->uid)
					{
						glm::mat4 tmp;
						auto a = (Cube*)i->content();
						if (myE->getMod() == INC)
						{
							a->rotate(45.0f);
						}
						else
						{
							a->rotate(-45.0f);
						}
						
						return true;
					}
				}
			}
		}
		if (eventType == EventType::Position)
		{
			PositionEvent* myE = dynamic_cast<PositionEvent*>(&e);

			if (myE)
			{

				for (auto i : worldObjects)
				{
					if (i->content()->getID() == myE->uid)
					{
						glm::mat4 tmp;
						auto a = (Cube*)i->content();
						auto p = a->getPosition();
						if (myE->getMod() == INC)
						{
							p.x += 2.0f;
							a->setPosition(p);
						}
						else
						{
							p.x -= 2.0f;
							a->setPosition(p);
						}

						return true;
					}
				}
			}
		}
		return false;
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
		for (size_t j = 0; j < objects.size() && isSphere(objects[i]->content()->type); ++j)
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
					if(collideSphere) resolveSphereSphereCollision(dynamic_cast<Sphere*>(objects[i]->content()), dynamic_cast<Sphere*>(objects[j]->content()));
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

	auto pointOnPlane = obj2->getPosition();
	glm::vec3 planeNormal = obj2->getNormal(); // Retrieve the plane's normal vector
	float planeDistance = -glm::dot(planeNormal, obj2->getPosition()); // Compute the distance from the origin using the plane's normal and a point on the plane (e.g., obtained from getPosition())


	glm::vec3 pointOnPlaneLocal = planeNormal * planeDistance; // Get a point on the plane in local space
	glm::vec3 pointOnPlaneWorld = glm::vec3(obj2->getTransform() * glm::vec4(pointOnPlaneLocal, 1.0f)); // Transform the point to world space using the plane's transformation matrix

	pointOnPlane = pointOnPlaneLocal;
	auto sub = point - pointOnPlane;
	auto norm = obj2->getNormal();

	float dist = std::abs(glm::dot(sub, norm));

	if (dist > rad1) { // The sphere is not currently intersecting the plane
		return false;
	}

	// Additional checks: see if the sphere is still within bounds


	glm::vec3 projectedPoint = point - dist * norm;
	glm::quat planeRotation = obj2->getRotation();
	glm::vec3 rotatedProjectedPoint = pointOnPlane + glm::rotate(glm::inverse(planeRotation), projectedPoint - pointOnPlane);

	// Finite plane details
	float planeHalfWidth = obj2->xScale;
	float planeHalfHeight = obj2->yScale;

	// Check if the rotated projected point is within the finite plane
	return !(std::abs(rotatedProjectedPoint.x - pointOnPlane.x) > planeHalfWidth ||
		std::abs(rotatedProjectedPoint.y - pointOnPlane.y) > planeHalfHeight);


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

		glm::vec3 reflected = norm * (norm * vel) * 2.0f * 0.1f;

		/*glm::vec3* v = &obj1->getVelocity();
		*v -= reflected;*/

		auto v = &obj1->getVelocity();
		auto mag = glm::length(*v);

		*v = *v - norm * reflected;
		*v = *v + glm::vec3(0.0, 0.5, 0.1);
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

		glm::vec3 v1 = obj1->getVelocity();
		glm::vec3 v2 = obj2->getVelocity();
		float m1 = obj1->getMass(); // Get mass of sphere 1
		float m2 = obj2->getMass(); // Get mass of sphere 2

		glm::vec3 normal = glm::normalize(pos2 - pos1); // Calculate collision normal

		float impulse = (2.0f * m2) / (m1 + m2); // Calculate impulse factor

		nv1 = v1 + impulse * glm::dot(v2 - v1, normal) * normal; // Update velocity of sphere 1
		nv2 = v2 + impulse * glm::dot(v1 - v2, normal) * normal; // Update velocity of sphere 2

		obj1->setVelocity(nv1); // Set new velocity for sphere 1
		obj2->setVelocity(nv2); // Set new velocity for sphere 2

	}
}

