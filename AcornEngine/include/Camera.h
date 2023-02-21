#include "AcornData.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glfw3.h>

class Camera {

public:

	glm::vec3 Position;
	glm::vec3 Direction;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 Front;

	float Yaw;
	float Pitch;
	float MovementSpeed;
	float Zoom;

	Camera();

	void updatePosition(glm::vec3 newPosition);

	glm::vec3 GetPosition();

	glm::vec3 GetDirection();

	glm::vec3 GetUp();

	glm::vec3 GetFront();

	glm::vec3 GetRight();

	void MoveForward();
	void MoveBackward();
	void MoveRight();
	void MoveLeft();

	glm::mat4 LookAt(glm::vec3 targetPosition);

	//GetView();

private:

	const glm::vec3 START_POS = glm::vec3(0.0f, 0.0f, 3.0f);
	const glm::vec3 START_TARGET = glm::vec3(0.0f, 0.0f, 0.0f);
	const float d_YAW = -90.0f;
	const float d_PITCH = 0.0f;
	const float cameraSpeed = 100.0f;
	float getSpeed() const;


	//Used to produce orthogonal vector (e.g. rightVector).
	const glm::vec3 UP_VECTOR = glm::vec3(0.0f, 1.0f, 0.0f);


};