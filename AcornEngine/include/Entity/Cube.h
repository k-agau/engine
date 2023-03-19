#ifndef CUBE_H
#define CUBE_H

#include "Entity/Entity_Impl.h"
#include <iostream>

class Cube : public EntityImpl
{
private:
	Entity_Type CUBE;

	glm::mat4 transform;
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
	glm::mat4 rotate();
	glm::vec3 getTranslation();
};

class Plane : public EntityImpl
{
private:
	Entity_Type PLANE;

	glm::mat4 transform;
	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;
	//rotation
public:
	Plane(std::string _debugName, uint8_t _x, uint8_t _y, uint8_t _z);
	virtual ~Plane();
	void onCreate() override;
	void onDelete() override;
	void onUpdate() override;
	void onEvent(Event& event) override;
	glm::mat4 getTransform() override;
	glm::mat4 rotate();
	glm::vec3 getTranslation();
};

#endif // CUBE_H