#include <glad.h>
#include <glfw3.h>
#include "WindowManager.h"
#include "Renderer.h"


class AcornApp {


public:

	AcornApp();

	void init();
	void render();
	void Shutdown();
	GLFWwindow* GetWindow();

	bool WindowIsOpen();

private:

	static AcornApp* instance;
	WindowManager* windowManager;
	Renderer* renderer;

};
