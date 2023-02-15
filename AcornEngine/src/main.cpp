#include "AcornApp.h"

int main()
{
	AcornApp* App = new AcornApp();
	return 0;
}
/*
void processInput(GLFWwindow* window, float Object[], Camera& myC)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5 * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		myC.updatePosition(myC.GetPosition() + cameraSpeed * myC.GetFront());
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		myC.updatePosition(myC.GetPosition() -
			glm::normalize(
				glm::cross(myC.GetFront(), myC.GetUp())) * cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		myC.updatePosition(myC.GetPosition() - cameraSpeed * myC.GetFront());
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		myC.updatePosition(myC.GetPosition() +
			myC.GetRight() * cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		WIREFRAME = !WIREFRAME;
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		int8_t i = 9;
		int offset = Object[19];
		int rowOffset = 0;
		float rPoint = Object[18];
		while (i < 18) {
			if (Object[offset + i + 1 + rowOffset] <= 0.0) {
				offset = (offset + 1) % 3;
				Object[19] = offset;
			}
			Object[offset + i + rowOffset] -= 0.001;
			Object[offset + i + 1 + rowOffset] += 0.001;

			i += 3;
			++rowOffset;
		}

	}

	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
		int8_t i = 9;
		int offset = Object[19];
		int rowOffset = 0;
		float rPoint = Object[18];
		while (i < 18) {
			if (Object[offset + i + 1 + rowOffset] <= 0.0) {
				offset = (offset + 1) % 3;
				Object[19] = offset;
			}
			Object[offset + i + rowOffset] += 0.001;
			Object[offset + i + 1 + rowOffset] -= 0.001;

			i += 3;
			++rowOffset;
		}

	}

}*/