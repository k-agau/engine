#ifndef ENTITY_IMPL_H
#define ENTITY_IMPL_H

#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cstdint>
#include <string>

enum ENTITY_TYPE {
	CUBE,
	PLANE,
	SPHERE_LOW,
	SPHERE_MID,
	SPHERE_HIGH,
	CAMERA,
	Last
};

enum COLORS {

	RED,
	BLUE,
	GREEN,
	ORANGE,
	YELLOW,
	PURPLE

};

class EntityImpl
{
protected:

	int ID = -1;
	bool applyPhysics = false;
	bool applyCollision = false;

	COLORS color = RED;
	float  mass  = 5.0f;

	glm::vec3 force	   = glm::vec3(0, 0, 0);
	glm::vec3 velocity = glm::vec3(0, 0, 0);
	glm::vec3 position = glm::vec3(0, 0, 0);

	std::string debugName;

public:

	ENTITY_TYPE type;

	EntityImpl(ENTITY_TYPE _type, std::string _debugName, glm::vec3 pos);
	virtual ~EntityImpl();

	//Pure Virtuals
	virtual void onCreate() = 0;
	virtual void onDelete() = 0;
	virtual void onUpdate() = 0;
	virtual void onEvent(Event& event) = 0;
	virtual glm::mat4 getTransform() = 0;

	//Virtual Get Functions
	//can be overridden if you want to prevent access
	virtual glm::vec3& getForce()	 const { return const_cast<glm::vec3&>(force); };
	virtual glm::vec3& getVelocity() const { return const_cast<glm::vec3&>(velocity); };
	virtual glm::vec3& getPosition() const { return const_cast<glm::vec3&>(position); };
	virtual float	   getMass()	 const { return mass; };

	//Object Settings
	inline void setApplyPhysics(bool apply)    { applyPhysics = apply; };
	inline void setApplyCollision(bool apply)  { applyCollision = apply; };
	inline void setID(unsigned int newID)	   { ID = newID; }
	inline int	 getID()					   { return ID; }
	inline COLORS getColor()				   { return color; }
	inline void setColor(COLORS c)             { color = c; }
	inline bool getApplyPhysics()			   { return applyPhysics; };


};

#endif // ENTITY_IMPL_H