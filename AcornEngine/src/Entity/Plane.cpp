#include "Entity/Plane.h"
extern float dt;
Plane::Plane(std::string _debugName, uint8_t _x, uint8_t _y, uint8_t _z) :
	EntityImpl(ENTITY_TYPE::PLANE, _debugName, _x, _y, _z, true)
{
	calculateTransform();
}

Plane::~Plane()
{

}

void Plane::onCreate()
{

	std::cout << "Creating Plane" << std::endl;

}

void Plane::onDelete()
{
	std::cout << "Deleting Plane" << std::endl;
}

void Plane::onUpdate()
{
	std::cout << "Updating Plane" << std::endl;
}

void Plane::onEvent(Event& event)
{
	std::cout << "Event for Plane triggered" << std::endl;
}

void Plane::applyScale(glm::vec3 s) 
{
	scale = s;
}

void Plane::calculateTransform() {

	glm::mat4 rot = glm::toMat4(glm::quat(rotation));

	transform = 
		glm::translate(glm::mat4(1.0f), position) *
		glm::scale(glm::mat4(1.0f), scale) * 
		rot;

}

glm::mat4 Plane::getTransform()
{
	return transform;
}

glm::mat4 Plane::rotate() {

	transform = glm::rotate(transform, glm::radians(20.0f) * dt, glm::vec3(0.5f, 1.0f, 0.0f));
	return transform;

}