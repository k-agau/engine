#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"
#include "Entity/EntityManager.h"

#include "Layers/Layer.h"
#include "Menus/MenuManager.h"

#include <glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>

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

	std::vector<std::vector<unsigned int>> typeProperties;
	std::unordered_map<COLORS, glm::vec3> entityColors;
	std::vector<float> normals;
  
	MenuManager* menuManager;

	glm::mat4 M, V, P;
	Entity* L;
	int modelShaderLoc, 
		viewShaderLoc, 
		projectionShaderLoc, 
		colorShaderLoc,
		cameraShaderLoc,
		lightLoc;

	void initGeom();
	void initCube();
	void initPlane();
	void initSphere();
	void initEntityColors();
	void renderWorld(Layer* layer);

	inline bool isSphere(ENTITY_TYPE type) {
		return type == ENTITY_TYPE::SPHERE_LOW ||
			   type == ENTITY_TYPE::SPHERE_MID ||
			   type == ENTITY_TYPE::SPHERE_HIGH;
	}
};

const int VAO_IDX = 0;
const int VBO_IDX = 1;
const int CBO_IDX = 2;
const int EBO_IDX = 3;

#endif // RENDERER_H
