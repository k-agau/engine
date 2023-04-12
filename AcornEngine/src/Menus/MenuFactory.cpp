#include "Menus/MenuFactory.h"

ColorButton* MenuFactory::makeColorButton(const EventCallbackFn& f, Event e, COLORS b, COLORS h, glm::mat4 t, glm::vec3 pos)
{
	return new ColorButton(f, e, b, h, t, pos);
}

Menu* MenuFactory::makeEntityMenu(int id) 
{

	float X_OFFSET = 2.4;
	float Y_OFFSET = 2.0;

	ScaleEvent newEvent(id, INC);
	Menu* m = new Menu(menuV, ORANGE, menuP);
	glm::vec3 menuF = glm::normalize(glm::vec3(menuV[2]));

	Button* b = (Button*)new ColorButton(cb, newEvent, BLUE, GREEN, menuV, menuP);
	m->addButton(b);
	glm::vec3 pos = glm::vec3(b->getTransform()[3][0], b->getTransform()[3][1], b->getTransform()[3][2]);
	b->setTransform(glm::translate(b->getTransform(), glm::vec3(2.75f, 1.0f, -11.9f)));
	


	glm::vec3 buttonPos = glm::project(glm::vec3(menuP[0],menuP[1], 0.0), b->getTransform(), 
		glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f), 
		glm::vec4(0.0, 0.0, 800.0f, 600.0f));
	buttonPos[0] = (2.0f * buttonPos[0]) / 600.0f - 1.0f;
	buttonPos[1] = 1.0f - (2.0f * buttonPos[1]) / 800.0f;
	b->xLower = buttonPos[0] - 0.05;
	b->xUpper = buttonPos[0] + 0.2;
	b->yUpper = buttonPos[1] + 0.05;
	b->yLower = buttonPos[1] - 0.2;

	b = (Button*)new ColorButton(cb, newEvent, BLUE, GREEN, menuV, menuP);
	b->setTransform(glm::translate(b->getTransform(), glm::vec3(5.15f, 1.0f, -11.9f)));
	m->addButton(b);
	buttonPos = glm::project(glm::vec3(menuP[0], menuP[1], 0.0), b->getTransform(),
		glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f),
		glm::vec4(0.0, 0.0, 800.0f, 600.0f));

	buttonPos[0] = ((2.0f * buttonPos[0]) / 600.0f - 1.0f) + 0.35;
	buttonPos[1] = 1.0f - (2.0f * buttonPos[1]) / 800.0f;
	b->xLower = buttonPos[0] - 0.05;
	b->xUpper = buttonPos[0] + 0.2;
	b->yUpper = buttonPos[1] + 0.05;
	b->yLower = buttonPos[1] - 0.2;



	return m;

}