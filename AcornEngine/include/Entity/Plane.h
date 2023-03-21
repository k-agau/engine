#ifndef PLANE_H
#define PLANE_H

#include "Entity/Entity_Impl.h"
#include <iostream>

class Plane : public EntityImpl
{
private:
	ENTITY_TYPE PLANE;

	glm::mat4 transform;
	glm::vec3 rotation;
	glm::vec3 scale;

public:
	Plane(std::string _debugName, uint8_t _x, uint8_t _y, uint8_t _z);
	virtual ~Plane();
	void onCreate() override;
	void onDelete() override;
	void onUpdate() override;
	void onEvent(Event& event) override;
	glm::mat4 getTransform() override;
	glm::mat4 rotate();
};

#endif // PLANE_H