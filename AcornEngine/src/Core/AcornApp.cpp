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
		HandleCollisions(dt);
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

void AcornApp::HandleCollisions(float dt)
{
	auto objects = EntityManager::instance()->getWorldEntities();

	for (size_t i = 0; i < objects.size(); ++i)
	{
		for (size_t j = i + 1; j < objects.size(); ++j)
		{
			if (objects[i]->content()->type & (SPHERE_HIGH | SPHERE_MID | SPHERE_LOW))
			{
				if (objects[j]->content()->type & PLANE)
				{
					resolveSpherePlaneCollision(dynamic_cast<Sphere*>(objects[i]->content()), dynamic_cast<Plane*>(objects[j]->content()));
				}
				else if (objects[j]->content()->type & CUBE)
				{
					resolveSphereCubeCollision(dynamic_cast<Sphere*>(objects[i]->content()), dynamic_cast<Cube*>(objects[j]->content()));
				}
				else if (objects[j]->content()->type & (SPHERE_HIGH | SPHERE_MID | SPHERE_LOW))
				{
					resolveSphereSphereCollision(dynamic_cast<Sphere*>(objects[i]->content()), dynamic_cast<Sphere*>(objects[j]->content()));
				}
				else
				{
					std::cout << "NOT YET IMPLEMENTED" << std::endl;
				}
			}
		}
	}
}

bool AcornApp::checkSpherePlaneCollision(Sphere* obj1, Plane* obj2)
{
	int rad1 = obj1->getRadius();
	auto vert1 = obj1->getVertices();
	auto vert1Size = obj1->getVertexSize();

	auto planePos = obj2->getPosition();

	float dist =
		std::pow(planePos[2] - *(vert1 + 0), 2) +
		std::pow(planePos[1] - *(vert1 + 1), 2) +
		std::pow(planePos[0] - *(vert1 + 2), 2);

	dist = std::sqrt(dist);

	return dist <= rad1;
}

bool AcornApp::checkSphereSphereCollision(Sphere* obj1, Sphere* obj2)
{
	int rad1 = obj1->getRadius(), rad2 = obj2->getRadius();
	auto vert1 = obj1->getVertices(), vert2 = obj1->getVertices();
	auto vert1Size = obj1->getVertexSize(), vert2Size = obj2->getVertexSize();

	float dist =
		std::pow(*(vert2 + 0) - *(vert1 + 0), 2) +
		std::pow(*(vert2 + 1) - *(vert1 + 1), 2) +
		std::pow(*(vert2 + 2) - *(vert1 + 2), 2);

	dist = std::sqrt(dist);

	return dist <= rad1 + rad2;
}

void AcornApp::resolveSpherePlaneCollision(Sphere* obj1, Plane* obj2)
{
	if (checkSpherePlaneCollision(obj1, obj2))
	{
		auto forceOfSphere = obj1->getForce();
		auto forceOfPlane = obj2->getForce();


	}
}

void AcornApp::resolveSphereCubeCollision(Sphere* obj1, Cube* obj2)
{

}

void AcornApp::resolveSphereSphereCollision(Sphere* obj1, Sphere* obj2)
{
	if (checkSphereSphereCollision(obj1, obj2))
	{




	}
}
