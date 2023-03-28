#include "Menus/MenuFactory.h"

ColorButton* MenuFactory::makeColorButton(void* func())
{
	return new ColorButton(void* func());
}

Menu* MenuFactory::makeEntityMenu(Entity* entity) {

	Menu* m = new Menu(glm::vec3(1, 1, 1), glm::vec3(1.0f, 1.0f, 1.0f));

	m->addButton(new ColorButton(
		[entity]() {entity->content()->getForce(); },
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)));

	return m;

}