#include "KeyCodes.h"
class Event {

public:

	enum EventType{

		None,
		WindowClose,
		WindowResize,
		KeyEvent,
		KeyPressed,
		KeyReleased,
		MousePressed,
		MouseReleased,
		MouseMoved
	};

	virtual ~Event() = default;

	bool Handled = false;

	virtual EventType GetEventType() { return eventType; }
	virtual void SetEventType(EventType e) { eventType = e; }
	virtual void ToString() const { std::cout<<"DEFAULT_EVENT_TEXT"; }

protected:
	EventType eventType;

};