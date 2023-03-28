#include "Menus/Menu.h"

Menu::Menu(glm::vec3 s, glm::vec3 c) :
	scale(s), color(c)
{
	area = new Plane("menu", 0, 0, 0);
	area->scale(s);
}