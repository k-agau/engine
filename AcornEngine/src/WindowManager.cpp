#include "WindowManager.h"

WindowManager::WindowManager()
{
}

WindowManager::~WindowManager()
{
}

bool WindowManager::init(int const width, int const height)
{
	return false;
}

void WindowManager::shutdown()
{
}

void WindowManager::setEventIndirection(EventCallbacks* callbacks_in)
{
	callbacks = callbacks_in;
}

GLFWwindow* WindowManager::getHandle()
{
	return window;
}
