#include "Core/AcornApp.h"

float dt;
float lastFrame;

void updateDeltaTime() {
	float currentFrame = glfwGetTime();
	dt = currentFrame - lastFrame;
	lastFrame = currentFrame;
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
	}

	Shutdown();
}

void AcornApp::render() {

	if (renderer) {
		renderer->Update();
		glfwSwapBuffers(GetWindow());
		glfwPollEvents();
		updateDeltaTime();
	}
}

GLFWwindow* AcornApp::GetWindow()
{
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
