#include "Layers/MenuLayer.h"

#include "Entity/Entity_Impl.h"
#include "Layers/LayerStack.h"

MenuLayer::MenuLayer(): Layer("MenuLayer", true)
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
	LayerStack::instance()->popOverlay(this);
}

void MenuLayer::onUpdate()
{

}

bool MenuLayer::onEvent(Event& event)
{
	if (event.GetEventType() == EventType::KeyPressed)
	{
		KeyPressedEvent* myE = dynamic_cast<KeyPressedEvent*>(&event);

		if (myE) {

			switch (myE->getKeyCode()) {
			case Key::B:
				onDetach();
				break;
			default:
				std::cout << "ERROR" << std::endl;
			}
		}
	}
	return true;
}