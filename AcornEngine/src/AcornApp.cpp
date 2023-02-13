#include "AcornApp.h"

AcornApp* AcornApp::instance = nullptr;

AcornApp::AcornApp() {

	if (instance == nullptr) {

		instance = this;

	}

}

void AcornApp::init() {

	windowManager = new WindowManager();
	windowManager->init(600, 800);

	renderer = new Renderer();
	renderer->init();

}

void AcornApp::render() {

	if (instance && instance == this && renderer) {
		this->renderer->Update();
		glfwSwapBuffers(GetWindow());
		glfwPollEvents();
	}

}

GLFWwindow* AcornApp::GetWindow() {

	if (instance && instance == this && windowManager) 
		return windowManager->getHandle();

}

void AcornApp::Shutdown() {

	if (instance && instance == this) {
		renderer->Shutdown();
		windowManager->shutdown();
	}

}

bool AcornApp::WindowIsOpen() {

	return !glfwWindowShouldClose(GetWindow());

}