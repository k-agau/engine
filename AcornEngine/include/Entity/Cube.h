#ifndef CUBE_H
#define CUBE_H

#include "Entity/Entity_Impl.h"
#include <iostream>

class Cube : public EntityImpl
{
private:
	ENTITY_TYPE CUBE;

	glm::mat4 transform;
	//rotation
public:
	Cube(std::string _debugName, uint8_t _x, uint8_t _y, uint8_t _z);
	virtual ~Cube();
	void onCreate() override;
	void onDelete() override;
	void onUpdate() override;
	void onEvent(Event& event) override;
	glm::mat4 getTransform() override;
	glm::mat4 rotate();

	glm::vec3* getPosition() override { return &position; };
	glm::vec3* getVelocity() override { return &velocity; };
	float getMass() override { return this->mass; };
	glm::vec3* getForce() override { return &force; };
};
#endif // CUBE_H