#include "Core/WindowManager.h"

WindowManager* WindowManager::inst = nullptr;

WindowManager* WindowManager::instance()
{
	if (WindowManager::inst == nullptr) {
		WindowManager::inst = new WindowManager;
	}
	return inst;
}

WindowManager::~WindowManager()
{
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
		return false;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return 0;
	}

	std::printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

	glfwSetWindowUserPointer(window, static_cast<void*>(this));

	/*DEFINE GLFW CALLBACKS*/

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			auto self = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
			switch (action) {

			case GLFW_PRESS:
			{
				KeyPressedEvent newEvent(key, false);
				self->callback(newEvent);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent newEvent(key);
				self->callback(newEvent);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent newEvent(key, true);
				self->callback(newEvent);
				break;
			}

			}
		});

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
		{
			auto self = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));

			MouseMoveEvent newEvent((float)xPos, (float)yPos);
			self->callback(newEvent);

		});
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{

			auto self = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent newEvent(button);
				self->callback(newEvent);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent newEvent(button);
				self->callback(newEvent);
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
