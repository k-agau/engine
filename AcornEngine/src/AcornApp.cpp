#include "AcornApp.h"

AcornApp::AcornApp() {

	windowManager = new WindowManager();
	windowManager->init(600, 800);

}

GLFWwindow* AcornApp::GetWindow() {

	if (windowManager) return windowManager->getHandle();

}

void AcornApp::Shutdown() {

	windowManager->shutdown();

}