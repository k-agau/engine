#include "Shader.h"
#include "Camera.h"
#include <glad.h>
#include <glm/gtc/type_ptr.hpp>

class Renderer {


public:

	Renderer();

	void init();
	void Update();
	void Shutdown();

	unsigned int VBO, VAO;

private:

	static Renderer* instance;

	Shader* shaderManager;
	Camera* rCamera;
	glm::mat4 M, V, P;


	void initGeom();

};