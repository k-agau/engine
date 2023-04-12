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
	glm::mat4 getTransform() override;
	void calculateTransform();
	void applyScale(glm::vec3 s);
	COLORS color;
	//Demo Functions
	glm::mat4 rotate(float angle);
	glm::mat4 transform;

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
};

#endif // PLANE_H