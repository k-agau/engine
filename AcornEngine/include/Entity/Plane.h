#ifndef PLANE_H
#define PLANE_H

#include "Entity/Entity_Impl.h"
#include <iostream>

class Plane : public EntityImpl
{
public:

	Plane(std::string _debugName, glm::vec3 pos);
	Plane(std::string _debugName, glm::vec3 pos, bool menu);
	virtual ~Plane();
	void onCreate() override;
	void onDelete() override;
	void onUpdate() override;
	void onEvent(Event& event) override;

	glm::vec3 getForward();

	glm::vec3 getNormal();

	glm::mat4 getTransform() override;
	glm::mat4 getRotation();

	COLORS color;
	//Demo Functions
	void rotatevec3(glm::vec3 r);
	glm::mat4 rotate(float degrees = 90.0f);
	glm::vec3 forward;

	glm::mat4 transform;
	glm::mat4 rotation;
	glm::vec3 scale;

	float xScale = 10.0;
	float yScale = 10.0;
	float noScale = 10.0;
	bool isMenu = false;
private:
	glm::vec3 normal;
};

#endif // PLANE_H
