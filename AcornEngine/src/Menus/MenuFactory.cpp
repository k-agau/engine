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

	float centerX = WIDTH / 2.0f;
	float centerY = HEIGHT / 2.0f;
	float y_off = 0.0;
	float x_screen_off = 131;
	float y_screen_off = 109;
	float button_width = 25.0f;

	ScaleEvent* newEvent = new ScaleEvent(id, INC);
	Menu* m = new Menu(menuV, BLUE, menuP);
	Button* b = nullptr;
	int j = 0;
	for (int i = 1; i < 7; ++i)
	{
		if (i % 2)
		{
			//create button
			b = (Button*)new ColorButton(cb, (buttonEventMap[(i - 1) % 3](id, DEC)), WHITE, BLACK, menuV, menuP);
			m->addButton(b);
			b->setTransform(glm::translate(b->getTransform(), glm::vec3(2.6f, 3.8f + y_off, -11.9f)));

			//caclulate bounds in screen space
			b->x = centerX + 151;
			b->y = 300 - 218 + y_screen_off * j;
			b->yLower = b->y - button_width;
			b->yUpper = b->y + button_width;
			b->xLower = b->x - button_width;
			b->xUpper = b->x + button_width;
		}
		else
		{
			//create button
			b = (Button*)new ColorButton(cb, (buttonEventMap[(i - 2) % 3](id, INC)), WHITE, BLACK, menuV, menuP);
			m->addButton(b);
			b->setTransform(glm::translate(b->getTransform(), glm::vec3(4.8f, 3.8f + y_off, -11.9f)));

			//caclulate bounds in screen space
			b->x = 400 + 151 + x_screen_off;
			b->y = 300 - 218 + y_screen_off * j;
			b->yLower = b->y - button_width;
			b->yUpper = b->y + button_width;
			b->xLower = b->x - button_width;
			b->xUpper = b->x + button_width;

			y_off -= 2.0;  ++j;
		}
	}
	return m;

}
