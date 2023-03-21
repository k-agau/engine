#ifndef CUBE_H
#define CUBE_H

#include "Entity/Entity_Impl.h"
#include <iostream>

class Cube : public EntityImpl
{
private:
	Entity_Type CUBE;

	glm::vec3 translation;
	glm::vec3 rotation; 
	glm::vec3 scale;
//rotation
public:
	Cube(std::string _debugName, uint8_t _x, uint8_t _y, uint8_t _z);
	virtual ~Cube();
	void onCreate() override;
	void onDelete() override;
	void onUpdate() override;
	void onEvent(Event& event) override;
	glm::mat4 getTransform() override; 
};

#endif // CUBE_H