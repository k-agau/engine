#include "Camera.h"
#include <iostream>
Camera::Camera()
{
	Position = START_POS;
	Direction = glm::normalize(Position - START_TARGET);
	std::cout << UP_VECTOR[0] << UP_VECTOR[1] << UP_VECTOR[2]<< std::endl;
	std::cout << Direction[0] << Direction[1] << Direction[2]<< std::endl;
	Right = glm::normalize(glm::cross(UP_VECTOR, Direction));
	Up = glm::cross(Direction, Right);
	Front = glm::vec3(0.0, 0.0, -1.0);
}

void Camera::updatePosition(glm::vec3 newPosition)
{
	Position = newPosition;
}

glm::vec3 Camera::GetPosition()
{
	return this->Position;
}

glm::vec3 Camera::GetDirection()
{
	return Direction;
}

glm::vec3 Camera::GetUp()
{
	return Up;
}

glm::vec3 Camera::GetFront()
{
	return Front;
}

glm::vec3 Camera::GetRight()
{
	return Right;
}

glm::mat4 Camera::LookAt(glm::vec3 targetPosition)
{
	return glm::lookAt(Position, targetPosition, UP_VECTOR);
}


