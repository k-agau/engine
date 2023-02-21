#include "Shader.h"
#include "Entity/EntityManager.h"
#include <glad.h>
#include <glm/gtc/type_ptr.hpp>

class Renderer {
public:

	static Renderer* instance();
	void init();
	void Update();
	void Shutdown();
	EntityManager* getEntityManager();

	unsigned int VBO, VAO, CBO, EBO;

private:
	Renderer() = default;
	static Renderer* inst;
	Shader* shaderManager;
	EntityManager* entityManager;

	glm::mat4 M, V, P;
	void initGeom();
};