#include "Menus/Menu.h"

Menu::Menu(glm::mat4 t, COLORS c, glm::vec3 p) :
	color(c),
	scale(glm::vec3(0.2, 0.4, 1.0))
{
	area = new Plane("menu", p, true);
	area->transform = t;
	area->transform = glm::translate(area->transform, glm::vec3(0.15, 0.0, 0.0));
	area->transform = glm::scale(area->transform, scale);
	area->scale = scale;
	area->color = c;
}