#include "Entity/Cube.h"

Cube::Cube(std::string _debugName, glm::vec3 pos) :
	EntityImpl(ENTITY_TYPE::CUBE, _debugName, pos)

{
	rotation = glm::vec3(1, 1, 1);
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
		* glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(1.0, 0.0, 0.0))
		* glm::scale(glm::mat4(1.0f), scale);
}

glm::mat4 Cube::rotate(float degrees) {

	rot += degrees;
	return getTransform();

}