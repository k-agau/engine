#include "Entity/Cube.h"

Cube::Cube(std::string _debugName, uint8_t _x, uint8_t _y, uint8_t _z):
	EntityImpl(Entity_Type::CUBE, _debugName, _x, _y, _z)
{
	translation = glm::vec3(_x, _y, _z);
	rotation = glm::vec3(1, 1, 1);
	scale = glm::vec3(1, 1, 1);
	transform = getTransform();
}

Cube::~Cube()
{

}

void Cube::onCreate()
{

	std::cout << "Creating Cube" << std::endl;

}

void Cube::onDelete()
{
	std::cout << "Deleting Cube" << std::endl;
}

void Cube::onUpdate()
{
	std::cout << "Updating Cube" << std::endl;
}

void Cube::onEvent(Event& event)
{
	std::cout << "Event for Cube triggered" << std::endl;
}

glm::mat4 Cube::getTransform()
{
	glm::mat4 rot = glm::toMat4(glm::quat(rotation));

	return glm::translate(glm::mat4(1.0f), translation)
		 * glm::scale(glm::mat4(1.0f), scale);
}

glm::mat4 Cube::rotate() {

	transform = glm::rotate(transform, glm::radians(0.01f), glm::vec3(0.5f, 1.0f, 0.0f));
	return transform;

}

glm::vec3 Cube::getTranslation() { //adsf 
	return translation;
}

//--------------------------------- PLANE

Plane::Plane(std::string _debugName, uint8_t _x, uint8_t _y, uint8_t _z) :
	EntityImpl(Entity_Type::PLANE, _debugName, _x, _y, _z)
{
	translation = glm::vec3(_x, _y, _z);
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

	return glm::translate(glm::mat4(1.0f), translation)
		* glm::scale(glm::mat4(1.0f), scale);
}

glm::mat4 Plane::rotate() {

	transform = glm::rotate(transform, glm::radians(0.01f), glm::vec3(0.5f, 1.0f, 0.0f));
	return transform;

}

glm::vec3 Plane::getTranslation() { //adsf 
	return translation;
}


