#include "AcornApp.h"

extern double deltaTime;

double getElapsedTime() {
	static double lasttime = glfwGetTime();
	double actualtime = glfwGetTime();
	double difference = actualtime - lasttime;
	lasttime = actualtime;
	return difference;
}

AcornApp::AcornApp(): windowManager(nullptr), renderer(nullptr), layers(nullptr)
{
	windowManager = WindowManager::instance();
	windowManager->init(600, 800);

	renderer = Renderer::instance();
	renderer->init();

	layers = LayerStack::instance();
	windowManager->SetEventCallBack(layers->distributeEvent());
}

void AcornApp::run()
{
	while (WindowIsOpen())
	{
		render();
		deltaTime = getElapsedTime();
	}
	 
	Shutdown();
}

void AcornApp::render() {

	if (renderer) {
		renderer->Update();
		glfwSwapBuffers(GetWindow());
		glfwPollEvents();
	}
}

GLFWwindow* AcornApp::GetWindow() {

	if (windowManager)
		return windowManager->getHandle();
}

void AcornApp::Shutdown() {
	renderer->Shutdown();
	windowManager->shutdown();
}

bool AcornApp::WindowIsOpen() {

	return !glfwWindowShouldClose(GetWindow());
}