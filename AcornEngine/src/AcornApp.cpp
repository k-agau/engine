#include "AcornApp.h"

//AcornApp* AcornApp::inst = nullptr;
//
//AcornApp* AcornApp::instance()
//{
//	if (AcornApp::inst == nullptr)
//	{
//		inst = new AcornApp();
//	}
//
//	return inst;
//}

AcornApp::AcornApp(): windowManager(nullptr), renderer(nullptr)
{
	windowManager = WindowManager::instance();
	windowManager->init(600, 800);

	renderer = Renderer::instance();
	renderer->init();
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