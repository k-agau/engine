#include "Core/Renderer.h"
#include "Layers/LayerStack.h"

Renderer* Renderer::inst = nullptr;

Renderer* Renderer::instance() {

	if (Renderer::inst == nullptr) {
		Renderer::inst = new Renderer;
	}
	return inst;
}

void Renderer::init()
{
	//enter alternate paths in constructor, if wanted
	shaderManager = new Shader();
	entityManager = EntityManager::instance();

	M = glm::mat4(1.0f);
	V = glm::mat4(1.0f);
	P = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	//Initialize data connection points to shaders
	modelShaderLoc = glGetUniformLocation(shaderManager->ID, "model");
	viewShaderLoc = glGetUniformLocation(shaderManager->ID, "view");
	projectionShaderLoc = glGetUniformLocation(shaderManager->ID, "projection");
	colorShaderLoc = glGetUniformLocation(shaderManager->ID, "entityColor");

	initGeom();

}

void Renderer::initGeom()
{
	for (int i = (int)ENTITY_TYPE::CUBE; i < (int)ENTITY_TYPE::Last; ++i)
	{
		typeProperties.push_back(std::vector<unsigned int>(4, 0));
	}

	initCube();
	initPlane();               
	initSphere();
	initEntityColors();

	float i = -12.5f;
	for (auto color : entityColors) 
	{
		auto e = entityManager->addSphereToWorld(glm::vec3(i, 0, -20), SPHERE_HIGH);
		e->content()->setColor(color.first);
		i += 5;
	}
	
	//entityManager->addPlaneToWorld(glm::vec3(0, 0, 0));

}

void Renderer::Update()
{

	for (auto it = LayerStack::instance()->begin(); it != LayerStack::instance()->end(); ++it)
	{
		if ((*it)->layerName == "World")
		{
			renderWorld(*it);
		}
		else
		{
			std::cout << "ERROR: invalid layer" << std::endl;
		}
	}
}

void Renderer::renderWorld(Layer* layer)
{

	// Clear canvas
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Update view
	V = entityManager->updateView();

	// Activate shaders
	shaderManager->use();

	for (auto& e : entityManager->getWorldEntities()) 
	{
		ENTITY_TYPE entityType = e->content()->type;

		//intalize approporiate data objects
		glBindVertexArray(typeProperties[entityType][VAO_IDX]);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		//get transform
		M = e->content()->getTransform();

		//update matracies
		glUniformMatrix4fv (modelShaderLoc, 1, GL_FALSE, glm::value_ptr(M));
		glUniformMatrix4fv (viewShaderLoc, 1, GL_FALSE, glm::value_ptr(V));
		glUniformMatrix4fv (projectionShaderLoc, 1, GL_FALSE, glm::value_ptr(P));
		glUniform3fv	   (colorShaderLoc, 1, glm::value_ptr(entityColors[e->content()->getColor()]));

		//draw
		if (isSphere(entityType))
		{
			Sphere* s = (Sphere*)e->content();
			glDrawElements(GL_TRIANGLES, s->getIndexCount(), GL_UNSIGNED_INT, (void*)0);
		}
		else 
		{
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}
			

		//disable gl arrays
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindVertexArray(0);
		
	}

	entityManager->worldStep();

}

void Renderer::Shutdown()
{
	for (int i = 0; i < 1; ++i)
	{
		glDeleteVertexArrays(1, &typeProperties[i][0]);
		glDeleteBuffers(1, &typeProperties[i][1]);
	}
	shaderManager->~Shader();
}

void Renderer::initCube()
{
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

	int cubeLoc = (int)ENTITY_TYPE::CUBE;

	/*NEW OBJECT*/
	glGenVertexArrays(1, &typeProperties[cubeLoc][VAO_IDX]); // VAO
	glBindVertexArray(typeProperties[cubeLoc][VAO_IDX]);

	/*NEW OBJECT VERTEX BUFFER*/
	glGenBuffers(1, &typeProperties[cubeLoc][VBO_IDX]); // VBO
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

	glBindBuffer(GL_ARRAY_BUFFER, typeProperties[cubeLoc][VBO_IDX]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

	// vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	/*NEW OBJECT VERTEX BUFFER*/
	glGenBuffers(1, &typeProperties[cubeLoc][CBO_IDX]); // CBO
	//set the current state to focus on our vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, typeProperties[cubeLoc][CBO_IDX]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &typeProperties[cubeLoc][EBO_IDX]); // EBO

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, typeProperties[cubeLoc][EBO_IDX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeElements), cubeElements, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Renderer::initPlane()
{
	float plane[] = {

		-1.0,-1.0,0.0,
		-1.0,1.0,0.0,
		1.0,-1.0,0.0,
		1.0,1.0,0.0,

	};

	float planeColors[] =
	{

		1.0,0.0,0.0,
		0.0,1.0,0.0,
		0.0,0.0,1.0,
		0.0,1.0,1.0,

	};

	unsigned int planeElements[] =
	{

		0,1,2,
		1,2,3,

	};

	int planeLoc = (int)ENTITY_TYPE::PLANE;

	glGenVertexArrays(1, &typeProperties[planeLoc][VAO_IDX]);
	glBindVertexArray(typeProperties[planeLoc][VAO_IDX]);

	/*NEW OBJECT VERTEX BUFFER*/
	glGenBuffers(1, &typeProperties[planeLoc][VBO_IDX]);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

	glBindBuffer(GL_ARRAY_BUFFER, typeProperties[planeLoc][VBO_IDX]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plane), plane, GL_STATIC_DRAW);

	// vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	/*NEW OBJECT VERTEX BUFFER*/
	glGenBuffers(1, &typeProperties[planeLoc][CBO_IDX]);
	//set the current state to focus on our vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, typeProperties[PLANE][CBO_IDX]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeColors), planeColors, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &typeProperties[planeLoc][EBO_IDX]);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, typeProperties[planeLoc][EBO_IDX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeElements), planeElements, GL_STATIC_DRAW);

	glBindVertexArray(0);

}

void Renderer::initSphere()
{

	for (int sphereLoc = (int)ENTITY_TYPE::SPHERE_LOW; sphereLoc <= (int)ENTITY_TYPE::SPHERE_HIGH; ++sphereLoc)
	{

		Sphere* s = (Sphere*)entityManager->addSphereToWorld(glm::vec3(0, 0, 0), (ENTITY_TYPE)sphereLoc)->content();

		glGenVertexArrays(1, &typeProperties[sphereLoc][VAO_IDX]);
		glBindVertexArray(typeProperties[sphereLoc][VAO_IDX]);

		/*NEW OBJECT VERTEX BUFFER*/
		glGenBuffers(1, &typeProperties[sphereLoc][VBO_IDX]);

		glBindBuffer(GL_ARRAY_BUFFER, typeProperties[sphereLoc][VBO_IDX]);

		glBufferData(
			GL_ARRAY_BUFFER, 
			s->getInterleavedVertexSize(),
			s->getInterleavedVertices(),
			GL_STATIC_DRAW);

		int j = 5;
		glGenBuffers(1, &typeProperties[sphereLoc][EBO_IDX]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, typeProperties[sphereLoc][EBO_IDX]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
			s->getIndexSize(),             // data size, # of bytes
			s->getIndices(),               // ptr to index data
			GL_STATIC_DRAW);  

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 32, (void*)0);
		
		glBindVertexArray(0);

		entityManager->removeEntity(s->getID());
	}
}

void Renderer::initEntityColors()
{
	entityColors.insert(std::pair(RED,    glm::vec3 (1.0f, 0.0f, 0.0f)));
	entityColors.insert(std::pair(BLUE,   glm::vec3(0.0f, 0.0f, 1.0f)));
	entityColors.insert(std::pair(GREEN,  glm::vec3(0.0f, 0.7f, 0.0f)));
	entityColors.insert(std::pair(ORANGE, glm::vec3(1.0f, 0.5f, 0.0f)));
	entityColors.insert(std::pair(YELLOW, glm::vec3(1.0f, 1.0f, 0.0f)));
	entityColors.insert(std::pair(PURPLE, glm::vec3(1.0f, 0.0f, 1.0f)));
}