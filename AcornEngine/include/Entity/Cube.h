#ifndef CUBE_H
#define CUBE_H

#include "Entity/Entity_Impl.h"
#include <iostream>

class Cube : public EntityImpl
{

public:
	Cube(std::string _debugName, glm::vec3 pos);
	virtual ~Cube();
	void onCreate() override;
	void onDelete() override;
	void onUpdate() override;
	void onEvent(Event& event) override;
	void setTransform(glm::mat4x4 t) { transform = t; };
	glm::mat4 getTransform() override;
	glm::vec3 getScale() { return scale; };
	glm::vec3 scale;
	//Demo Functions
	glm::mat4 rotate();

private:

	glm::mat4 transform;
	glm::vec3 rotation;

};
#endif // CUBE_H