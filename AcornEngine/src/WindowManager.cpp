#include "WindowManager.h"

WindowManager* WindowManager::instance = nullptr;

WindowManager::WindowManager() : window(nullptr)
{
	if (instance == nullptr) {
		instance = this;
		return;
	}

	std::cout << "WindowManager Singleton has already been declared.";
}

WindowManager::~WindowManager()
{
	if (instance == this) { instance = nullptr; }
}

bool WindowManager::init(int const width, int const height)
{
	/*GLFW INIT AND CONFIG*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	this->window = glfwCreateWindow(height, width, "AcornEngine.exe", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return 0;
	}

	std::printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

	/*DEFINE GLFW CALLBACKS*/

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			switch (action) {

			case GLFW_PRESS:
			{
				KeyPressedEvent newEvent(key, false);
				newEvent.ToString();
				//send to layer stack
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent newEvent(key);
				newEvent.ToString();
				//send to layer stack
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent newEvent(key, true);
				newEvent.ToString();
				//send to layer stack
			}

			}
		});

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
		{
			MouseMoveEvent newEvent((float)xPos, (float)yPos);
			newEvent.ToString();

		});
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{

			switch (action)
			{
			case GLFW_PRESS:
				{
					MouseButtonPressedEvent newEvent(button);
					newEvent.ToString();
					break;
				}
			case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent newEvent(button);
					newEvent.ToString();
					break;
				}
			}

		});
}

void WindowManager::shutdown()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* WindowManager::getHandle()
{
	return window;
}
