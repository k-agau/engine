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

	glm::vec3 getNormal();

	glm::mat4 getTransform() override;
	void calculateTransform();
	void applyScale(glm::vec3 s);
	COLORS color;
	//Demo Functions
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 front;
	glm::vec3 cUp;
	glm::vec3 cRight;
	glm::vec3 cFront;
	glm::vec3 worldUp = glm::vec3(0.0, 1.0, 0.0);

private:
	
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 rotate(float degrees = 90.0f);
	glm::vec3 forward;

	glm::mat4 transform;
	glm::vec3 rotation;
	glm::vec3 scale;

	float xScale = 5.0;
	float yScale = 5.0;
	float noScale = 5.0;
private:

};

#endif // PLANE_H