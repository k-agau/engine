// AcornEngine.cpp : Defines the entry point for the application.
//

#include "AcornEngine.h"
#include "Shader.h"
#include "Camera.h"
#include <glad.h>
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

bool WIREFRAME = 0;

	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window, float Object[], Camera& myC);

	int main()
	{

		/*GLFW INIT AND CONFIG*/
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		GLFWwindow* window = glfwCreateWindow(800, 600, "AcornEngine.exe", NULL, NULL);

		if (window == NULL)
		{
			cout << "Failed to create GLFW window" << endl;
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize OpenGL context" << std::endl;
			return 0;
		}

		printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);


		float triangle[] = {
				-1.0, -1.0,  1.0,
				1.0, -1.0,  1.0,
				1.0,  1.0,  1.0,
				-1.0,  1.0,  1.0,
				// back
				-1.0, -1.0, -1.0,
				1.0, -1.0, -1.0,
				1.0,  1.0, -1.0,
				-1.0,  1.0, -1.0,
				//tube 8 - 11
				-1.0, -1.0,  1.0,
				1.0, -1.0,  1.0,
				1.0,  1.0,  1.0,
				-1.0,  1.0,  1.0,
				//12 - 15
				-1.0, -1.0, -1.0,
				1.0, -1.0, -1.0,
				1.0,  1.0, -1.0,
				-1.0,  1.0, -1.0
		};
		unsigned int indices[] = {  // note that we start from 0!
			// front
			0, 1, 2,
			2, 3, 0,
			// back
			7, 6, 5,
			5, 4, 7,
			//tube 8-11, 12-15
			8,12,13,
			8,13,9,
			9,13,14,
			9,14,10,
			10,14,15,
			10,15,11,
			11,15,12,
			11,12,8
		};
		unsigned int VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

		unsigned int EBO;
		glGenBuffers(1, &EBO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(9 * sizeof(float)));
		glEnableVertexAttribArray(1);

		Shader myShader;
		Camera myCamera;

		/*MATRIX SPACE INIT*/
		//Model Mat
		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		//model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));

		//View Mat
		glm::mat4 view = glm::mat4(1.0f);
		// note that we're translating the scene in the reverse direction of where we want to move
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		//Projection Mat
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		while (!glfwWindowShouldClose(window))
		{
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			processInput(window, triangle, myCamera);

			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			//wireframe mode
			if (WIREFRAME) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


			/*GENERATE CAMERA ROTATION EFFECT
			const float radius = 10.0f;
			float camX = sin(glfwGetTime()) * radius;
			float camZ = cos(glfwGetTime()) * radius;
			myCamera.updatePosition(glm::vec3(camX, 0, camZ));
			view = myCamera.LookAt(glm::vec3(0, 0, 0));*/
			view = myCamera.LookAt(myCamera.GetPosition() + myCamera.GetFront());

			myShader.use();
			model = glm::rotate(model, glm::radians(0.01f), glm::vec3(0.5f, 1.0f, 0.0f));
			int modelLoc = glGetUniformLocation(myShader.ID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			int viewLoc = glGetUniformLocation(myShader.ID, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			int projectionLoc = glGetUniformLocation(myShader.ID, "projection");
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangle), triangle);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		myShader.~Shader();

		glfwTerminate();
		return 0;
	}

	void processInput(GLFWwindow* window, float Object[], Camera &myC)
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

	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}