#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include "Event.h"

class MouseMoveEvent : public Event {

public:

	MouseMoveEvent(float newX, float newY) :
		xPos(newX), yPos(newY) { SetEventType(MouseMoved);};

	float GetX() const { return xPos; }
	float GetY() const { return yPos; }

	void ToString() const override 
	{

		std::cout << "MouseMoveEvent: ("
			<< xPos << ", " << yPos << ")"
			<< std::endl;
	}

private:
	
	float xPos, yPos;

};

class MouseButtonEvent : public Event {

public:

	MouseCode GetMouseButton() const { return button; }

protected:
	
	MouseButtonEvent(MouseCode newButton) :
		button(newButton) {};
	
	MouseCode button; 
};

class MouseButtonPressedEvent : public MouseButtonEvent {

public:
	MouseButtonPressedEvent(MouseCode newButton) :
		MouseButtonEvent(newButton) { SetEventType(MousePressed); };

	void ToString() const override 
	{
		std::cout << "MouseButtonPressed: " << button << std::endl;
	}

};
class MouseButtonReleasedEvent : public MouseButtonEvent {

public:
	MouseButtonReleasedEvent(MouseCode newButton) :
		MouseButtonEvent(newButton) { SetEventType(MouseReleased); };

	void ToString() const override 
	{
		std::cout << "MouseButtonReleased: " << button << std::endl;
	}

};
#endif // MOUSE_EVENT_H