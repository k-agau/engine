#include <glad.h>
#include <glfw3.h>
#include "WindowManager.h"
#include "Renderer.h"
#include "Logs/Logger.h"

class AcornApp {
public:
	AcornApp();
	void run();
	void render();
	void Shutdown();
	GLFWwindow* GetWindow();
	bool WindowIsOpen();
private:
	WindowManager* windowManager;
	Renderer* renderer;
	Logger logger;
};
