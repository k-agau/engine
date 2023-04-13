#include "Menus/MenuFactory.h"

ColorButton* MenuFactory::makeColorButton(const EventCallbackFn& f, Event* e, COLORS b, COLORS h, glm::mat4 t, glm::vec3 pos)
{
	return new ColorButton(f, e, b, h, t, pos);
}

void MenuFactory::init()
{
	EventGenerator scale = [&](int id, ENTITY_EVENT_MOD mod)
	{
		return (Event*)new ScaleEvent(id, mod);
	};

	EventGenerator rotate = [&](int id, ENTITY_EVENT_MOD mod)
	{
		return (Event*)new RotateEvent(id, mod);
	};
	EventGenerator position = [&](int id, ENTITY_EVENT_MOD mod)
	{
		return (Event*)new PositionEvent(id, mod);
	};
	buttonEventMap.push_back(scale);
	buttonEventMap.push_back(rotate);
	buttonEventMap.push_back(position);
}

Menu* MenuFactory::makeEntityMenu(int id) 
{

	float X_OFFSET = 2.4;
	float y_off = 0.0;

	ScaleEvent* newEvent = new ScaleEvent(4, INC);
	Menu* m = new Menu(menuV, ORANGE, menuP);
	glm::vec3 menuF = glm::normalize(glm::vec3(menuV[2]));
	Button* b = nullptr;

	for (int i = 1; i < 7; ++i)
	{
		if (i % 2)
		{
			b = (Button*)new ColorButton(cb, (buttonEventMap[(i-1)%3](4, INC)), BLUE, GREEN, menuV, menuP);
			m->addButton(b);
			b->setTransform(glm::translate(b->getTransform(), glm::vec3(2.6f, 3.8f + y_off, -11.9f)));
		}
		else
		{
			b = (Button*)new ColorButton(cb, (buttonEventMap[(i-2)%3](4, DEC)), BLUE, GREEN, menuV, menuP);
			m->addButton(b);
			b->setTransform(glm::translate(b->getTransform(), glm::vec3(4.8f, 3.8f + y_off, -11.9f)));
			y_off -= 2.0;
		}
	}

	


	/*/glm::vec3 buttonPos = glm::project(glm::vec3(menuP[0], menuP[1], 0.0), b->getTransform(),
		glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f), 
		glm::vec4(0.0, 0.0, 800.0f, 600.0f));
	buttonPos[0] = (2.0f * buttonPos[0]) / 600.0f - 1.0f;
	buttonPos[1] = 1.0f - (2.0f * buttonPos[1]) / 800.0f;
	b->xLower = buttonPos[0] - 0.05;
	b->xUpper = buttonPos[0] + 0.2;
	b->yUpper = buttonPos[1] + 0.05;
	b->yLower = buttonPos[1] - 0.2;

	ScaleEvent* newEvent1 = new ScaleEvent(4, DEC);
	b = (Button*)new ColorButton(cb, newEvent1, BLUE, GREEN, menuV, menuP);
	
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

	ScaleEvent* newEvent2 = new ScaleEvent(4, DEC);
	b = (Button*)new ColorButton(cb, newEvent2, BLUE, GREEN, menuV, menuP);
	b->setTransform(glm::translate(b->getTransform(), glm::vec3(5.15f, -1.0f, -11.9f)));
	m->addButton(b);
	buttonPos = glm::project(glm::vec3(menuP[0], menuP[1], 0.0), b->getTransform(),
		glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f),
		glm::vec4(0.0, 0.0, 800.0f, 600.0f));

	buttonPos[0] = ((2.0f * buttonPos[0]) / 600.0f - 1.0f) + 0.35;
	buttonPos[1] = 1.0f - (2.0f * buttonPos[1]) / 800.0f;
	b->xLower = buttonPos[0] - 0.05;
	b->xUpper = buttonPos[0] + 0.2;
	b->yUpper = buttonPos[1] + 0.05;
	b->yLower = buttonPos[1] - 0.2;*/



	return m;

}