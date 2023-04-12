#ifndef COLLISION_H
#define COLLISION_H

#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Visitor.h"

struct CollisionPoints
{
	glm::vec3 A;
	glm::vec3 B;
	glm::vec3 Normal;
	float Depth;
	bool HasCollision;
};

struct Transform
{
	glm::vec3 Pos;
	glm::vec3 Scale;
	glm::quat Rotation;
};

class Cube;
class Plane;

class Collision {
public:
	void TestCollision(const Cube& objA, const Plane& objB);
	void TestCollision(const Cube& objA, const Cube& objB);
	void TestCollision(const Plane& objA, const Cube& objB);
	void TestCollision(const Plane& objA, const Plane& objB);
};

#endif // COLLISION_H