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

struct SphereCollider;
struct PlaneCollider;

namespace algo
{
	CollisionPoints FindSphereSphereCollisionPoints(
		const SphereCollider* a, const Transform* ta,
		const SphereCollider* b, const Transform* tb);

	CollisionPoints FindSpherePlaneCollisionPoints(
		const SphereCollider* a, const Transform* ta,
		const PlaneCollider* b, const Transform* tb);

	CollisionPoints FindPlaneSphereCollisionPoints(
		const PlaneCollider* a, const Transform* ta,
		const SphereCollider* b, const Transform* tb);
}

struct Collider
{
	virtual CollisionPoints TestCollision(
		const Transform* transform,
		const Collider* collider,
		const Transform* colliderTransform
	) const = 0;

	virtual CollisionPoints TestCollision(
		const Transform* transform,
		const SphereCollider* Sphere,
		const Transform* SphereTransform
	) const = 0;

	virtual CollisionPoints TestCollision(
		const Transform* transform,
		const PlaneCollider* plane,
		const Transform* planeTransform
	) const = 0;
};

struct SphereCollider : Collider
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

	CollisionPoints TestCollision(
		const Transform* transform,
		const SphereCollider* Sphere,
		const Transform* SphereTransform
	) const override
	{
		return algo::FindSphereSphereCollisionPoints(
			this, transform, Sphere, SphereTransform);
	}

	CollisionPoints TestCollision(
		const Transform* transform,
		const PlaneCollider* plane,
		const Transform* planeTransform
	) const override
	{
		return algo::FindSpherePlaneCollisionPoints(
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
		const SphereCollider* Sphere,
		const Transform* SphereTransform
	) const override
	{
		return algo::FindPlaneSphereCollisionPoints(this, transform, Sphere, SphereTransform);
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

#endif // COLLISION_H