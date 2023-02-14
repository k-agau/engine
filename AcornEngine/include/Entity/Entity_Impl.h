#ifndef ENTITY_IMPL_H
#define ENTITY_IMPL_H

#include "Events/Event.h"
#include <cstdint>
#include <string>

class EntityImpl
{
protected:
	uint8_t type;
	std::string debugName;

	uint8_t x;
	uint8_t y;
	uint8_t z;
public:
	EntityImpl(uint8_t _type, std::string _debugName, uint8_t _x, uint8_t _y, uint8_t _z);
	virtual ~EntityImpl();

	virtual void onCreate() = 0;
	virtual void onDelete() = 0;
	virtual void onUpdate() = 0;
	virtual void onEvent(Event& event) = 0;
};

#endif // ENTITY_IMPL_H