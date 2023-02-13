#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

class WindowManager {

public:

	WindowManager();
	~WindowManager();

	//Don't 
	WindowManager(const WindowManager&) = delete;
	WindowManager& operator= (const WindowManager&) = delete;


	bool init(int const width, int const height);
	void shutdown();

	GLFWwindow* getHandle();

private:

	static WindowManager* instance; 
	GLFWwindow* window;
};