#include "Core/Camera.h"
#include <iostream>

double deltaTime = 0.0;

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

void Camera::updateMousePositions(float xpos, float ypos)
{
	lastX = xpos;
	lastY = ypos;
}

void Camera::changeCameraYawAndPitch(float xpos, float ypos)
{
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	Front = glm::normalize(direction);
}

void Camera::MoveForward() 
{
	Position += cameraSpeed * Front;
}

void Camera::MoveBackward()
{
	Position -= cameraSpeed * Front;
}
void Camera::MoveRight()
{
	Position += glm::normalize(glm::cross(Front, Up)) * cameraSpeed;
}

void Camera::MoveLeft()
{
	Position -= glm::normalize(glm::cross(Front, Up)) * cameraSpeed;
}

glm::mat4 Camera::LookAt(glm::vec3 targetPosition)
{
	return glm::lookAt(Position, targetPosition, UP_VECTOR);
}



