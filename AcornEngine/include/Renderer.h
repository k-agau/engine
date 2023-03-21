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

	float colorChanger = 0.0;
	bool goUp = true;

	unsigned int VBO, VAO, CBO, EBO;
	unsigned int pVBO, pVAO, pCBO, pEBO;

private:
	Renderer() = default;
	static Renderer* inst;
	Shader* shaderManager;
	EntityManager* entityManager;

	glm::mat4 M, V, P;
	void initGeom();
};