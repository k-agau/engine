#include "Renderer.h"

Renderer* Renderer::inst = nullptr;

Renderer* Renderer::instance() {

	if (Renderer::inst == nullptr) {
		Renderer::inst = new Renderer;
	}
	return inst;

}
void Renderer::init() {

	//enter alternate paths in constructor, if wanted
	shaderManager = new Shader();
	entityManager = EntityManager::instance();

	M = glm::mat4(1.0f);
	V = glm::mat4(1.0f);
	P = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	initGeom();

}

void Renderer::initGeom() {


	//DEFINITION OF A CUBE
	float cube[] = {
		-1.0, -1.0,  1.0,
		1.0, -1.0,  1.0,
		1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,
		// back
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0,  1.0, -1.0,
		-1.0,  1.0, -1.0,
		//tube 8 - 11
		-1.0, -1.0,  1.0,
		1.0, -1.0,  1.0,
		1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,
		//12 - 15
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0,  1.0, -1.0,
		-1.0,  1.0, -1.0
	};

	unsigned int cubeElements[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// back
		7, 6, 5,
		5, 4, 7,
		//tube 8-11, 12-15
		8,12,13,
		8,13,9,
		9,13,14,
		9,14,10,
		10,14,15,
		10,15,11,
		11,15,12,
		11,12,8
	};


	GLfloat cube_colors[] = {
		// front colors
		1.0, 0.0, 0.5,
		1.0, 0.0, 0.5,
		1.0, 0.0, 0.5,
		1.0, 0.0, 0.5,
		// back colors
		0.5, 0.5, 0.0,
		0.5, 0.5, 0.0,
		0.5, 0.5, 0.0,
		0.5, 0.5, 0.0,
		// tube colors
		0.0, 1.0, 1.0,
		0.0, 1.0, 1.0,
		0.0, 1.0, 1.0,
		0.0, 1.0, 1.0,
		0.0, 1.0, 1.0,
		0.0, 1.0, 1.0,
		0.0, 1.0, 1.0,
		0.0, 1.0, 1.0,
	};

	/*NEW OBJECT*/
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	/*NEW OBJECT VERTEX BUFFER*/
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

	// vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	/*NEW OBJECT VERTEX BUFFER*/
	glGenBuffers(1, &CBO);
	//set the current state to focus on our vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeElements), cubeElements, GL_STATIC_DRAW);

	glBindVertexArray(0);

	entityManager->addCubeToWorld();
	M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));

}

EntityManager* Renderer::getEntityManager()
{
	return entityManager;
}

void Renderer::Update() {

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//wireframe mode
	//if (WIREFRAME) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	V = entityManager->updateView();
	glm::vec3 PlayerPos = glm::vec3(0.0, 0.1f, -0.1f);
	auto M1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.1f, -0.1f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	shaderManager->use();
	for (auto& e : entityManager->getWorldEntities()) {
		M = e->content()->getTransform();
		//M = glm::rotate(M, glm::radians(0.01f), glm::vec3(0.5f, 1.0f, 0.0f));
		int modelLoc = glGetUniformLocation(shaderManager->ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(M));
		int viewLoc = glGetUniformLocation(shaderManager->ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(V));
		int projectionLoc = glGetUniformLocation(shaderManager->ID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(P));

		//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangle), triangle);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);

}

void Renderer::Shutdown() {

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	shaderManager->~Shader();

}