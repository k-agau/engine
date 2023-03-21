#ifndef ENTITY_IMPL_H
#define ENTITY_IMPL_H

#include "Events/KeyEvent.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cstdint>
#include <string>

enum ENTITY_TYPE {
	CUBE,
	PLANE,
	CAMERA,
	Last
};

class EntityImpl
{
protected:

	std::string debugName;

public:

	ENTITY_TYPE type;

	EntityImpl(ENTITY_TYPE _type, std::string _debugName, uint8_t _x, uint8_t _y, uint8_t _z);
	virtual ~EntityImpl();

	float mass = 5.0f;
	glm::vec3 force = glm::vec3(0, 0, 0);
	glm::vec3 velocity = glm::vec3(0, 0, 0);
	glm::vec3 position;

	virtual void onCreate() = 0;
	virtual void onDelete() = 0;
	virtual void onUpdate() = 0;
	virtual void onEvent(Event& event) = 0;
	virtual glm::mat4 getTransform() = 0;
	virtual glm::mat4 rotate() = 0;

};

#endif // ENTITY_IMPL_H