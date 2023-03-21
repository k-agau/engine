#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <functional>

class WindowManager {

public:

	using EventCallbackFn = std::function<void(Event&)>;

	static WindowManager* instance();
	~WindowManager();

	bool init(int const width, int const height);
	void shutdown();
	GLFWwindow* getHandle();
	const void SetEventCallBack(const EventCallbackFn& f) { callback = f; }
	EventCallbackFn callback;

private:

	WindowManager() = default;
	static WindowManager* inst;
	GLFWwindow* window;
	
};

#endif // WINDOW_MANAGER_H