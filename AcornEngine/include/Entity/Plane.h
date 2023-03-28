#ifndef PLANE_H
#define PLANE_H

#include "Entity/Entity_Impl.h"
#include <iostream>

class Plane : public EntityImpl
{
private:
	ENTITY_TYPE PLANE;

	glm::mat4 transform;
	void calculateTransform();

public:
	Plane(std::string _debugName, uint8_t _x, uint8_t _y, uint8_t _z);
	virtual ~Plane();
	void onCreate() override;
	void onDelete() override;
	void onUpdate() override;
	void onEvent(Event& event) override;
	glm::mat4 getTransform() override;
	void applyScale(glm::vec3 s);
	glm::mat4 rotate();

	glm::vec3 color;

	glm::vec3* getPosition() override { return &position; };
	glm::vec3* getVelocity() override { return &velocity; };
	float getMass() override { return this->mass; };
	glm::vec3* getForce() override { return &force; };
};

#endif // PLANE_H