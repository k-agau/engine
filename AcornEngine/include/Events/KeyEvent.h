#include "Event.h"

class KeyEvent : public Event {

public:

	KeyCode getKeyCode() const { return EventKeyCode; }

protected:

	KeyEvent(const KeyCode keycode) :
		EventKeyCode(keycode) {};

	KeyCode EventKeyCode;

};

class KeyPressedEvent : public KeyEvent {

public:

	KeyPressedEvent(const KeyCode keycode, bool is_repeat) :
		KeyEvent(keycode), isRepeat(is_repeat) {
		SetEventType(KeyPressed);
	}

	bool IsRepeat() const { return isRepeat; }

	void ToString() const override
	{
		std::cout << "KeyPressedEvent: "
			<< EventKeyCode << " (repeat = "
			<< isRepeat << ")" << std::endl;
	}

private:
	bool isRepeat;
};

class KeyReleasedEvent : public KeyEvent {

public:

	KeyReleasedEvent(const KeyCode keycode) :
		KeyEvent(keycode) {
		SetEventType(KeyReleased);
	}

	void ToString() const override
	{
		std::cout << "KeyReleasedEvent: " << EventKeyCode << std::endl;
	}
};