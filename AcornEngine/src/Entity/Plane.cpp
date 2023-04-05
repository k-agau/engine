#include "Entity/Plane.h"

Plane::Plane(std::string _debugName, glm::vec3 pos) :
	EntityImpl(ENTITY_TYPE::PLANE, _debugName, pos)
{
	rotation = glm::vec3(1, 1, 1);
	scale = glm::vec3(1, 1, 1);
	transform = getTransform();
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

glm::mat4 Plane::getTransform()
{
	glm::mat4 rot = glm::toMat4(glm::quat(rotation));
	
	return glm::translate(glm::mat4(1.0f), position)
		* glm::scale(glm::mat4(1.0f), scale);
}

glm::mat4 Plane::rotate() {

	transform = glm::rotate(transform, glm::radians(0.01f), glm::vec3(0.5f, 1.0f, 0.0f));
	return transform;

}