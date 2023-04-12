#include "Entity/Plane.h"

extern float dt;

Plane::Plane(std::string _debugName, glm::vec3 pos) :
	EntityImpl(ENTITY_TYPE::PLANE, _debugName, pos)
{
	rotation = glm::vec3(1.0, 5.0f,4.0f);
	scale = glm::vec3(1, 1, 1);
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
	calculateTransform();
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

glm::mat4 Plane::rotate(float angle) {

	calculateTransform();
	transform = glm::rotate(transform, 5.0f * dt,
		glm::vec3(0.0,1.0,0.0));
	calculateTransform();

	return transform;

}