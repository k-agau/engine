#include "Entity/Cube.h"

Cube::Cube(std::string _debugName, glm::vec3 pos) :
	EntityImpl(ENTITY_TYPE::CUBE, _debugName, pos)

{
	rotation = glm::mat4(1.0f);
	rot = 0.0;
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

	return glm::translate(glm::mat4(1.0f), position)
		* rotation
		* glm::scale(glm::mat4(1.0f), scale);
}

glm::mat4 Cube::rotate(float degrees) {

	rot += degrees;
	rotation = glm::rotate(rotation, glm::radians(degrees), currentAxis);
	return getTransform();

}