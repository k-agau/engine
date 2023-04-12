#include "Entity/Plane.h"

Plane::Plane(std::string _debugName, glm::vec3 pos) :
	EntityImpl(ENTITY_TYPE::PLANE, _debugName, pos)
{
	setColor(BLUE);
	rotation = glm::vec3(-0.97f, 0.5f, 0.0f);
	scale = glm::vec3(20.0, 20.0, 20.0);
	transform = getTransform();
	glm::mat4 invert = glm::inverse(transform);
	//forward = glm::normalize(glm::vec3(invert[2]));
	forward = glm::vec3(invert[2]);
	forward[0] *= scale[0];
	forward[1] *= scale[1];
	forward[2] *= scale[2];

	applyCollision = true;
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

	return glm::translate(glm::mat4(1.0), position) * rot
		* glm::scale(glm::mat4(1.0), scale);
}

glm::mat4 Plane::rotate(float degrees)
{
	transform = glm::rotate(transform, glm::radians(0.000001f), glm::vec3(0.0f, 1.0f, 0.0f));
	/*glm::mat4 invert = glm::inverse(transform);
	forward = glm::normalize(glm::vec3(invert[2]));*/
	return transform;
}

glm::vec3 Plane::getForward()
{
	return forward;
}
