#include "Layers/MenuLayer.h"

MenuLayer::MenuLayer(MenuManager* m) : Layer("Menu"), manager(m)
{

}

MenuLayer::~MenuLayer()
{

}

void MenuLayer::onAttach()
{

}

void MenuLayer::onDetach()
{

}

void MenuLayer::onUpdate()
{

}

bool MenuLayer::onEvent(Event& event)
{
	return manager->handleEvent(event);
}