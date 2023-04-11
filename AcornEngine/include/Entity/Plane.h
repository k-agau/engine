#ifndef PLANE_H
#define PLANE_H

#include "Entity/Entity_Impl.h"
#include <iostream>

class Plane : public EntityImpl
{
public:

	Plane(std::string _debugName, glm::vec3 pos);
	virtual ~Plane();
	void onCreate() override;
	void onDelete() override;
	void onUpdate() override;
	void onEvent(Event& event) override;

	glm::vec3 getForward();

	glm::mat4 getTransform() override;

	//Demo Functions
	glm::mat4 rotate(float degrees = 90.0f);
	glm::vec3 forward;

	glm::mat4 transform;
	glm::vec3 rotation;
	glm::vec3 scale;

private:

};

#endif // PLANE_H