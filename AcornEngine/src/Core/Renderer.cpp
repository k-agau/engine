#include "Core/Renderer.h"
#include "glm/gtx/vector_angle.hpp"

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
	menuManager = MenuManager::instance();

	M = glm::mat4(1.0f);
	V = entityManager->updateView();
	P = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	menuManager->init(LayerStack::instance()->distributeEvent(), V, entityManager->camera->GetPosition());

	//Initialize data connection points to shaders
	modelShaderLoc = glGetUniformLocation(shaderManager->ID, "model");
	viewShaderLoc = glGetUniformLocation(shaderManager->ID, "view");
	projectionShaderLoc = glGetUniformLocation(shaderManager->ID, "projection");
	colorShaderLoc = glGetUniformLocation(shaderManager->ID, "entityColor");
	cameraShaderLoc = glGetUniformLocation(shaderManager->ID, "viewPos");
	lightLoc = glGetUniformLocation(shaderManager->ID, "lightPos");
	
	std::cout << glGetError() << std::endl;

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
		e->content()->setApplyPhysics(false);
		i += 5;

	}
	
	menuManager->createEntityMenu();
	//entityManager->addPlaneToWorld(glm::vec3(0.0, 0.0, 0.0));
	L = entityManager->addCubeToWorld(glm::vec3(10.0, 5.0, 0.0));
	L->content()->setColor(WHITE);



	
//
//	
//	entityManager->addCubeToWorld(glm::vec3(0, 0, 0));
//	entityManager->addCubeToWorld(glm::vec3(10.0, 20.0, 0.0));
//	entityManager->addSphereToWorld(glm::vec3(5.0, 0.0, 0.0), SPHERE_MID);
//
//=======
	Entity* tmp = entityManager->addPlaneToWorld(glm::vec3(0, 2.0, 0.0));
	//tmp->rotate(glm::vec3(-0.97f, 0.5f, 0.0f));
	//auto transform = &tmp->content()->getTransform();
	//*transform = glm::rotate(tmp->content()->getTransform(), 90.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	//tmp->content()->setApplyCollision(true);

}

void Renderer::Update()
{

	// Clear canvas
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Update views
	V = entityManager->updateView();
	menuManager->updateCam(V, entityManager->camera->GetPosition());
	glm::vec3 C = entityManager->camera->GetPosition();

	//light dem
	L->content()->getPosition()[0] = 1.0f + sin(glfwGetTime()) * 2.0f;
	L->content()->getPosition()[2] = -10.0f + sin(glfwGetTime()) * 10.0;

	//necessary gpu updates
	glUniformMatrix4fv(projectionShaderLoc, 1, GL_FALSE, glm::value_ptr(P));
	glUniform3fv(cameraShaderLoc, 1, glm::value_ptr(C));
	glUniform3fv(lightLoc, 1, glm::value_ptr(L->content()->getPosition()));
	glUniformMatrix4fv(viewShaderLoc, 1, GL_FALSE, glm::value_ptr(V));
	// Activate shaders
	shaderManager->use();

	for (auto it = LayerStack::instance()->begin(); it != LayerStack::instance()->end(); ++it)
	{
		if ((*it)->layerName == "World" || (*it)->layerName == "Menu")
		{
			renderWorld(*it);
		}
		else
		{
			std::cout << "ERROR: invalid layer" << std::endl;
		}
	}

	entityManager->worldStep();

}

void Renderer::renderWorld(Layer* layer)
{


	if (layer->layerName == "World")
	{

		for (auto& e : entityManager->getWorldEntities())
		{
			ENTITY_TYPE entityType = e->content()->type;

			//intalize approporiate data objects
			glBindVertexArray(typeProperties[entityType][VAO_IDX]);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);

			//get transform
			M = e->content()->getTransform();

			//update uniforms
			glUniformMatrix4fv(modelShaderLoc, 1, GL_FALSE, glm::value_ptr(M));
			glUniform3fv(colorShaderLoc, 1, glm::value_ptr(entityColors[e->content()->getColor()]));

			//draw
			if (isSphere(entityType))
			{
				Sphere* s = (Sphere*)e->content();
				glDrawElements(GL_TRIANGLES, s->getIndexCount(), GL_UNSIGNED_INT, (void*)0);
			}
			else
			{
				if (entityType == ENTITY_TYPE::PLANE)
				{
					Plane* g = (Plane*)e->content();
					//g->rotate(2.0f);
				}
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}


			//disable gl arrays
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glBindVertexArray(0);

		}
	}
	else
	{

		glBindVertexArray(typeProperties[ENTITY_TYPE::PLANE][VAO_IDX]);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		for (auto m : menuManager->menus)
		{

			std::vector<Button*> menuButtons = *m->getButtons();

			M = m->getTransform();
			glUniformMatrix4fv(modelShaderLoc, 1, GL_FALSE, glm::value_ptr(M));
			glUniform3fv(colorShaderLoc, 1, glm::value_ptr(entityColors[m->color]));

			glDrawArrays(GL_TRIANGLES, 0, 36);


			for (auto b : menuButtons)
			{
				M = b->getTransform();

				glm::mat4 tmp = M * V * P;
				float x = (2.0f * menuManager->lastX) / 800.0f - 1.0f;
				float y = 1.0f - (2.0f * menuManager->lastY) / 600.0f;
				float z = 1.0f;
				glm::vec3 mousePos = glm::vec3(x, y, z);
				glm::vec3 O = glm::vec3(menuManager->lastX, menuManager->lastY, 0.0f);
				//glm::vec3 mousePos = glm::project(O,M, P, glm::vec4(0.0f,0.0f,800.0f,600.0f));
				//glm::vec3 O = glm::vec3(tmp[3][0], tmp[3][1], tmp[3][2
				/*
				for (int i = 0; i < 4; ++i)
				{
					for (int j = 0; j < 4; ++j)
					{
						std::cout << tmp[i][j] << ", ";
					}
					std::cout<< std::endl;
				}
				std::cout << std::endl;
				*/

				ColorButton* a = (ColorButton*)b;

					b->updateButton(mousePos.x, mousePos.y);
					entityManager->test = false;
			
				//update uniforms
				glUniformMatrix4fv(modelShaderLoc, 1, GL_FALSE, glm::value_ptr(M));
				glUniform3fv(colorShaderLoc, 1, glm::value_ptr(entityColors[a->getCurrentColor()]));
/*
			if (entityType == ENTITY_TYPE::PLANE)
			{
				 Plane* tmp = (Plane*)e->content();
				//M = tmp->rotate();
			}
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		}*/

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindVertexArray(0);
	}
	

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

	float cVertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	int cubeLoc = (int)ENTITY_TYPE::CUBE;

	glGenVertexArrays(1, &typeProperties[cubeLoc][VAO_IDX]);
	glGenBuffers(1, &typeProperties[cubeLoc][VBO_IDX]);

	glBindBuffer(GL_ARRAY_BUFFER, typeProperties[cubeLoc][VBO_IDX]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cVertices), cVertices, GL_STATIC_DRAW);

	glBindVertexArray(typeProperties[cubeLoc][VAO_IDX]);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}

void Renderer::initPlane()
{
	float plane[] = {


	//-1.0,-1.0,0.0, 0.0f,  0.0f, -1.0f,
	//-1.0,1.0,0.0, 0.0f,  0.0f, -1.0f,
	//1.0,-1.0,0.0, 0.0f,  0.0f, -1.0f,

	//1.0,1.0,0.0, 0.0f,  0.0f, 1.0f,
	//	-1.0,1.0,0.0, 0.0f,  0.0f, 1.0f,
	//1.0,-1.0,0.0, 0.0f,  0.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,


	};

	//float planeColors[] =
	//{

	//	1.0,0.0,0.0,
	//	0.0,1.0,0.0,
	//	0.0,0.0,1.0,
	//	0.0,1.0,1.0,

	//};

	//unsigned int planeElements[] =
	//{

	//	0,1,2,
	//	1,2,3,

	//};

	int planeLoc = (int)ENTITY_TYPE::PLANE;

	glGenVertexArrays(1, &typeProperties[planeLoc][VAO_IDX]);
	glGenBuffers(1, &typeProperties[planeLoc][VBO_IDX]);

	glBindBuffer(GL_ARRAY_BUFFER, typeProperties[planeLoc][VBO_IDX]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plane), plane, GL_STATIC_DRAW);

	glBindVertexArray(typeProperties[planeLoc][VAO_IDX]);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
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

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, false, 32, (void*)(sizeof(float) * 3));
		
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
	entityColors.insert(std::pair(BLACK,  glm::vec3(0.0f, 0.0f, 0.0f)));
	entityColors.insert(std::pair(WHITE,  glm::vec3(1.0f, 1.0f, 1.0f)));
}