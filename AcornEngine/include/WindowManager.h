#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

class WindowManager {

public:
	static WindowManager* instance();
	~WindowManager();
	bool init(int const width, int const height);
	void shutdown();
	GLFWwindow* getHandle();
private:
	WindowManager() = default;
	static WindowManager* inst;
	GLFWwindow* window;
};

#endif // WINDOW_MANAGER_H