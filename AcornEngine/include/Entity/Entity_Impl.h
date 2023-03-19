#ifndef ENTITY_IMPL_H
#define ENTITY_IMPL_H

#include "Events/KeyEvent.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cstdint>
#include <string>

enum Entity_Type {
	Null,
	CUBE,
	CAMERA,
	PLANE
};

class EntityImpl
{
protected:

	std::string debugName;

	uint8_t x;
	uint8_t y;
	uint8_t z;

public:

	Entity_Type type;

	EntityImpl(Entity_Type _type, std::string _debugName, uint8_t _x, uint8_t _y, uint8_t _z);
	virtual ~EntityImpl();

	virtual void onCreate() = 0;
	virtual void onDelete() = 0;
	virtual void onUpdate() = 0;
	virtual void onEvent(Event& event) = 0;
	virtual glm::mat4 getTransform() = 0;
};

#endif // ENTITY_IMPL_H