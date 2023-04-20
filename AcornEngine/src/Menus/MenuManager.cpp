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
	axisLoc = 0;
	axes.insert(std::pair(0, X_AXIS));
	axes.insert(std::pair(1, Y_AXIS));
	axes.insert(std::pair(2, Z_AXIS));
	currentAxis = axes[axisLoc];
	currentID = 4;
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
	camV = view; camP = pos;
	factory->updateFactoryCam(view, pos);
}

void MenuManager::updateMenuPos()
{
	if(!open)
	{
		float centerX = WIDTH / 2.0f;
		float centerY = HEIGHT / 2.0f;
		float y_off = 0.0;
		float x_screen_off = 131;
		float y_screen_off = 70;
		float button_width = 20.0f;

		auto m = menus[0];
		m->area->setPosition(camP);
		m->area->transform = camV;
		m->area->transform = glm::translate(m->area->transform, glm::vec3(0.22, 0.0, 0.0));
		m->area->transform = glm::scale(m->area->transform, m->area->scale);
		int i = 1; int j = 0;
		for (auto b : m->buttons)
		{
			b->area->setPosition(camP);
			b->area->setTransform(camV);
			b->area->setTransform(glm::scale(b->getTransform(), glm::vec3(0.006,0.006,0.01)));
			if (i % 2)
			{

				b->setTransform(glm::translate(b->getTransform(), glm::vec3(8.3f, 3.8f + y_off, -11.9f)));

				//caclulate bounds in screen space
				b->x = centerX + 300;
				b->y = 300 - 140 + y_screen_off * j;
				b->yLower = b->y - button_width;
				b->yUpper = b->y + button_width;
				b->xLower = b->x - button_width;
				b->xUpper = b->x + button_width;
			}
			else
			{
				b->setTransform(glm::translate(b->getTransform(), glm::vec3(10.0f, 3.8f + y_off, -11.9f)));

				//caclulate bounds in screen space
				b->x = 400 + 225 + x_screen_off;
				b->y = 300 - 140 + y_screen_off * j;
				b->yLower = b->y - button_width;
				b->yUpper = b->y + button_width;
				b->xLower = b->x - button_width;
				b->xUpper = b->x + button_width;

				y_off -= 2.0;  ++j;
			}
			++i;
		}
	}
	
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
			case Key::N: {
				if (!open)
				{
					focus = !focus;
					menus[0]->~Menu();
					menus.clear();
					createEntityMenu(currentID);
					return true;
				}

			}
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
					focus = false;
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
			case Key::LeftBracket: {

				if (!open)
				{
					menus[0]->buttons[togglePos]->onClick();
					return true;
				}

			}
			case Key::RightBracket: {

				if (!open)
				{
					menus[0]->buttons[togglePos+1]->onClick();
					return true;
				}

			}
			case Key::O: {

				if (!open)
				{
					currentAxis = axes[++axisLoc % 3];
					return true;
				}

			}
			case Key::Comma: {

				if (!open)
				{
					--currentID;
					menus[0]->setID(currentID);
					return true;
				}

			}
			case Key::Period: {

				if (!open)
				{
					++currentID;
					menus[0]->setID(currentID);
					
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

				return false;
			}

		}
	}
	else if (et == EventType::MousePressed)
	{

		MouseButtonPressedEvent* myE = dynamic_cast<MouseButtonPressedEvent*>(&e);

		if (myE)
		{
			if (!open)
			{
				for (auto b : menus[0]->buttons)
				{
					if (static_cast<ColorButton*>(b)->isBeingHovered())
					{
						b->onClick();
						break;
					}
				}

				return false;
			}

		}
	}

	return false;
}
