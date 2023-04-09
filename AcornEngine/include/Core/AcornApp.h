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
	void HandleCollisions(float dt);
	bool checkSpherePlaneCollision(Sphere* obj1, Plane* obj2);
	bool checkSphereSphereCollision(Sphere* obj1, Sphere* obj2);
	void resolveSpherePlaneCollision(Sphere* obj1, Plane* obj2);
	void resolveSphereCubeCollision(Sphere* obj1, Cube* obj2);
	void resolveSphereSphereCollision(Sphere* obj1, Sphere* obj2);
};