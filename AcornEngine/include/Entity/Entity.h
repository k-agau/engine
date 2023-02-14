#include "Events/Event.h"
#include <cstdint>
#include <string>

class Entity
{
protected:
	uint8_t type;
	std::string debugName;

	uint8_t x;
	uint8_t y;
	uint8_t z;
public:
	Entity(uint8_t _type, std::string _debugName, uint8_t _x, uint8_t _y, uint8_t _z);
	virtual ~Entity();

	virtual void onCreate() = 0;
	virtual void onDelete() = 0;
	virtual void onUpdate() = 0;
	virtual void onEvent(Event& event) = 0;
};