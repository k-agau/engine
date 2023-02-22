#include "Core/AcornApp.h"

extern double deltaTime;
double lastFrame;

void getElapsedTime() {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

AcornApp::AcornApp(): windowManager(nullptr), renderer(nullptr), layers(nullptr)
{
	windowManager = WindowManager::instance();
	windowManager->init(600, 800);

	renderer = Renderer::instance();
	renderer->init();

	layers = new LayerStack(renderer->getEntityManager());
	windowManager->SetEventCallBack(layers->distributeEvent());
}

void AcornApp::run()
{
	while (WindowIsOpen())
	{
		render();
		getElapsedTime();
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