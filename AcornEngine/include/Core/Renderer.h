#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"
#include "Entity/EntityManager.h"
#include "Menus/MenuManager.h"
#include <glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Layers/Layer.h"

class Renderer {
public:

	static Renderer* instance();
	void init();
	void Update();
	void Shutdown();
private:
	Renderer() = default;
	static Renderer* inst;
	Shader* shaderManager;
	EntityManager* entityManager;
	MenuManager* menuManager;

	glm::mat4 M, V, P;

	void initGeom();
	void initCube();
	void initPlane();
	void renderWorld(Layer* layer);

	std::vector<std::vector<unsigned int>> typeProperties;
};

const int VAO_IDX = 0;
const int VBO_IDX = 1;
const int CBO_IDX = 2;
const int EBO_IDX = 3;

#endif // RENDERER_H
