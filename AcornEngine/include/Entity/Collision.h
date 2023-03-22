#ifndef COLLISION_H
#define COLLISION_H

#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

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

struct Collider
{
	virtual CollisionPoints TestCollision(
		const Transform* transform,
		const Collider* collider,
		const Transform* colliderTransform
	) const = 0;

	virtual CollisionPoints TestCollision(
		const Transform* transform,
		const CubeCollider* cube,
		const Transform* cubeTransform
	) const = 0;

	virtual CollisionPoints TestCollision(
		const Transform* transform,
		const PlaneCollider* plane,
		const Transform* planeTransform
	) const = 0;
};

struct CubeCollider : Collider
{
	glm::vec3 Center;
	float Distance;

	CollisionPoints TestCollision(
		const Transform* transform,
		const Collider* collider,
		const Transform* colliderTransform
	) const override
	{
		return collider->TestCollision(colliderTransform, this, transform);
	}
	virtual CollisionPoints TestCollision(
		const Transform* transform,
		const CubeCollider* cube,
		const Transform* cubeTransform
	) const override
	{
		return algo::FindCubeCubeCollisionPoints(
			this, transform, cube, cubeTransform);
	}

	virtual CollisionPoints TestCollision(
		const Transform* transform,
		const PlaneCollider* plane,
		const Transform* planeTransform
	) const override
	{
		return algo::FindCubePlaneCollisionPoints(
			this, transform, plane, planeTransform);
	}
};

struct PlaneCollider : Collider
{
	glm::vec3 Center;
	float Radius;

	CollisionPoints TestCollision(
		const Transform* transform,
		const Collider* collider,
		const Transform* colliderTransform
	) const override
	{
		return collider->TestCollision(colliderTransform, this, transform);
	}

	virtual CollisionPoints TestCollision(
		const Transform* transform,
		const CubeCollider* cube,
		const Transform* cubeTransform
	) const override
	{
		return algo::FindPlaneCubeCollisionPoints(this, transform, cube, cubeTransform);
	}

	virtual CollisionPoints TestCollision(
		const Transform* transform,
		const PlaneCollider* plane,
		const Transform* planeTransform
	) const override
	{
		return {}; // Assume that two planes cannot collide
	}
};

namespace algo {
	CollisionPoints FindCubeCubeCollisionPoints(
		const CubeCollider* a, const Transform* ta,
		const CubeCollider* b, const Transform* tb);

	CollisionPoints FindCubePlaneCollisionPoints(
		const CubeCollider* a, const Transform* ta,
		const PlaneCollider* b, const Transform* tb);

	CollisionPoints FindPlaneCubeCollisionPoints(
		const PlaneCollider* a, const Transform* ta,
		const CubeCollider* b, const Transform* tb);
}

#endif // COLLISION_H