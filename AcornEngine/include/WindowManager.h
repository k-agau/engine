#include <glad.h>
#include <glfw3.h>

class EventCallbacks
{

public:


	virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;

	virtual void mouseCallback(GLFWwindow* window, int button, int action, int mods) = 0;

	virtual void resizeCallback(GLFWwindow* window, int in_width, int in_height) = 0;

};

class WindowManager {

public:

	WindowManager();
	~WindowManager();

	//Don't 
	WindowManager(const WindowManager&) = delete;
	WindowManager& operator= (const WindowManager&) = delete;


	bool init(int const width, int const height);
	void shutdown();

	void setEventIndirection(EventCallbacks* callbacks_in);
	GLFWwindow* getHandle();

	//bool OnEvent(Event &e);

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		if (key == GLFW_KEY_W && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		{
		}
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		{
		}
		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		{
		}
		if (key == GLFW_KEY_D && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		{

		}
		if (key == GLFW_KEY_J && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_J && action == GLFW_RELEASE)
		{
		}
		if (key == GLFW_KEY_L && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_L && action == GLFW_RELEASE)
		{
		}
		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		{
		}
		if (key == GLFW_KEY_D && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		{
		}
	}

	// callback for the mouse when clicked move the triangle when helper functions
	// written
	void mouseCallback(GLFWwindow* window, int button, int action, int mods)
	{
		double posX, posY;
		if (action == GLFW_PRESS)
		{
			glfwGetCursorPos(window, &posX, &posY);
			//Do something with mouse position here
			//std::cout << "Pos X " << posX <<  " Pos Y " << posY << std::endl;

		}
	}

	//if the window is resized, capture the new size and reset the viewport
	void resizeCallback(GLFWwindow* window, int in_width, int in_height)
	{
		//get the window size - may be different then pixels for retina
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
	}

private:

	GLFWwindow* window;
	EventCallbacks* callbacks;
};