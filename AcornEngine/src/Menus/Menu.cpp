#include "Menus/Menu.h"

Menu::Menu(glm::mat4 t, COLORS c, glm::vec3 p) :
	color(c),
	scale(glm::vec3(0.1, 0.4, 1.0))
{
	area = new Plane("menu", p, true);
	area->transform = t;
	area->transform = glm::translate(area->transform, glm::vec3(0.3, 0.0, 0.0));
	area->transform = glm::scale(area->transform, scale);
	area->scale = scale;
	area->color = c;
}

Menu::~Menu() 
{
	open = false;
	area->~Plane();
	for (auto i : buttons)
	{
		i->~Button();
	}

}

void Menu::setID(int id)
{
	for (auto i : buttons) { static_cast<EntityEvent*>(i->m_event)->uid = id; }
}