#include <glad.h>
#include <glfw3.h>
#include "WindowManager.h"
#include "Renderer.h"
#include "Logs/Logger.h"
#include "Layers/LayerStack.h"

class AcornApp {
public:
	AcornApp();
	void run();
private:
	WindowManager* windowManager;
	Renderer* renderer;
	Logger logger;
	LayerStack* layers;
	void render();
	void Shutdown();
	GLFWwindow* GetWindow();
	bool WindowIsOpen();
};