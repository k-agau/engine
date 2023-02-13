#include "WindowManager.h"


class AcornApp {


public:

	AcornApp();

	void Shutdown();
	GLFWwindow* GetWindow();

private:
	WindowManager* windowManager;
};
