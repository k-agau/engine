#ifndef EVENT_H
#define EVENT_H

#include "KeyCodes.h"
#include "MouseCodes.h"
#include <iostream>

enum EventType {

	None,
	WindowClose,
	WindowResize,
	KeyEvent,
	KeyPressed,
	KeyReleased,
	MousePressed,
	MouseReleased,
	MouseMoved,
	ScaleInc
};

enum ENTITY_EVENT_MOD {

	INC,
	DEC,
	X,
	Y,
	Z

};

class Event {

public:


	virtual ~Event() = default;

	bool Handled = false;

	virtual EventType GetEventType() { return eventType; }
	virtual void SetEventType(EventType e) { eventType = e; }
	virtual void ToString() const {  }

protected:
	EventType eventType;

};

#endif // EVENT_H