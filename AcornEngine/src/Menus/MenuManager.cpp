#include "Menus/MenuManager.h"

MenuManager* MenuManager::inst = nullptr;

MenuManager::MenuManager() : factory(nullptr)
{
	
}


void MenuManager::init(const EventCallbackFn& f, glm::mat4 view, glm::vec3 pos)
{
	callback = f;
	factory = new MenuFactory(callback);
	updateCam(view, pos);
}

MenuManager* MenuManager::instance()
{
	if (MenuManager::inst == nullptr)
	{
		inst = new MenuManager();
	}

	return inst;
}

void MenuManager::updateCam( glm::mat4 view, glm::vec3 pos )
{ 
	view[3][0] = 0.0f;  view[3][1] = 0.0f; view[3][2] = 0.0f;
	//view = glm::translate(view, pos);
	view = glm::inverse(view);
	view[3][0] = pos[0];  view[3][1] = pos[1]; view[3][2] = pos[2];
	factory->updateFactoryCam(view, pos);
}

Menu* MenuManager::createEntityMenu(int id)
{
	Menu* m = factory->makeEntityMenu(id);
	menus.push_back(m);
	return m;
}

bool MenuManager::handleEvent(Event& e)
{

	EventType et = e.GetEventType();

	if (et == EventType::KeyPressed)
	{
		KeyPressedEvent* myE = dynamic_cast<KeyPressedEvent*>(&e);

		if (myE)
		{
			switch (myE->getKeyCode())
			{
			case Key::M: {

				if (open)
				{
					createEntityMenu(currentID);
					open = !open;
				}
				else {
					menus[0]->~Menu();
					menus.clear();
					open = !open;
				}
				return true;
				
			}
			case Key::P: {

				if (!open)
				{
					togglePos = (togglePos + 2) % 6;
					return true;
				}

			}
			case Key::RightBracket: {

				if (!open)
				{
					menus[0]->buttons[togglePos]->onClick();
					return true;
				}

			}
			case Key::LeftBracket: {

				if (!open)
				{
					menus[0]->buttons[togglePos+1]->onClick();
					return true;
				}

			}
			}
		}
	}
	else if (et == EventType::MouseMoved)
	{

		MouseMoveEvent* myE = dynamic_cast<MouseMoveEvent*>(&e);

		if (myE) 
		{
			if (!open)
			{
				updateMousePositions(myE->GetX(), myE->GetY());

				return true;
			}

		}
	}


	return false;
}