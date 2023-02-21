#include "Entity/Cube.h"

Cube::Cube(std::string _debugName, uint8_t _x, uint8_t _y, uint8_t _z):
	EntityImpl(CUBE, _debugName, _x, _y, _z)
{
	translation = glm::vec3(0.0, 0.0f, 0.0f);
	rotation = glm::vec3(1, 1, 1);
	scale = glm::vec3(1, 1, 1);
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


