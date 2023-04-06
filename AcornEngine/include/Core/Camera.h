#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glfw3.h>

class Camera {

public:

	Camera();

	glm::vec3 Position;
	glm::vec3 Direction;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 Front;

	float yaw = - 90.0f;
	float pitch = 0;

	//to control camera yaw and pitch changes
	float lastX = 400.0f;
	float lastY = 300.0f;

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

	void updateMousePositions(float xpos, float ypos);
	void changeYawAndPitch(float xpos, float ypos);

	//GetView();

private:

	const glm::vec3 START_POS = glm::vec3(0.0f, 0.0f, 30.0f);
	const glm::vec3 START_TARGET = glm::vec3(0.0f, 0.0f, 0.0f);
	const float cameraSpeed = 1000.0f;

	//Used to produce orthogonal vector (e.g. rightVector).
	const glm::vec3 UP_VECTOR = glm::vec3(0.0f, 1.0f, 0.0f);


};