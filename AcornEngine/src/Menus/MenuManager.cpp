#include "Menus/MenuManager.h"

MenuManager* MenuManager::inst = nullptr;

MenuManager::MenuManager()
{
	factory = new MenuFactory();
}

MenuManager* MenuManager::instance()
{
	if (MenuManager::inst == nullptr)
	{
		inst = new MenuManager();
	}

	return inst;
}

Menu* MenuManager::createEntityMenu(Entity* entity)
{
	return factory->makeEntityMenu(entity);
}