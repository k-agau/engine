#include "Shader.h"
#include "Camera.h"
#include <glad.h>
#include <glm/gtc/type_ptr.hpp>

class Renderer {
public:
	static Renderer* instance();
	void init();
	void Update();
	void Shutdown();

	unsigned int VBO, VAO;

private:
	Renderer() = default;
	static Renderer* inst;
	Shader* shaderManager;
	Camera* rCamera;
	glm::mat4 M, V, P;
	void initGeom();
};