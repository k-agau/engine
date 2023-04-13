#include "Entity/Plane.h"

Plane::Plane(std::string _debugName, glm::vec3 pos) :
	EntityImpl(ENTITY_TYPE::PLANE, _debugName, pos)
{
	setColor(BLUE);
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 5.0f));
	position = trans * vec;
	rotation = glm::rotate(glm::mat4(1.0), glm::radians(-70.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	scale = glm::vec3(xScale, yScale, noScale);
	transform = getTransform();

	glm::mat4 invert = glm::inverse(transform);
	forward = glm::normalize(glm::vec3(invert[2]));

	applyCollision = true;

	//auto cntr = position;
	//glm::vec3 edge1 = b - a;
	//glm::vec3 edge2 = c - a;

	//normal = glm::cross(edge1, edge2);
	//normal = glm::normalize(normal);
	/*this->constant = -glm::dot(this->normal, a);
	this->normalize();*/

	// Extract the rotation part of the transformation matrix
	glm::mat3 rotation_matrix = glm::mat3(transform);

	// Compute the inverse transpose of the rotation matrix
	glm::mat3 inverse_transpose_rotation_matrix = glm::transpose(glm::inverse(rotation_matrix));

	// Extract the normal vector of the plane from the inverse transpose rotation matrix
	normal = glm::normalize(glm::vec3(inverse_transpose_rotation_matrix * glm::vec3(0.0f, 0.0f, 1.0f)));

	applyCollision = true;
}

Plane::Plane(std::string _debugName, glm::vec3 pos, bool menu) :
	isMenu(menu),
	EntityImpl(ENTITY_TYPE::PLANE, _debugName, pos)
{
	rotation = glm::rotate(glm::mat4(1.0), glm::radians(-89.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //glm::vec3(1.0, 1.0f, 1.0f);
	scale = glm::vec3(1, 1, 1);
}

Plane::~Plane()
{

}

void Plane::onCreate()
{

	std::cout << "Creating Plane" << std::endl;

}

void Plane::onDelete()
{
	std::cout << "Deleting Plane" << std::endl;
}

void Plane::onUpdate()
{
	std::cout << "Updating Plane" << std::endl;
}

void Plane::onEvent(Event& event)
{
	std::cout << "Event for Plane triggered" << std::endl;
}

glm::mat4 Plane::getTransform()
{
	return glm::translate(glm::mat4(1.0), position) * rotation
		* glm::scale(glm::mat4(1.0), scale);
}

void Plane::rotatevec3(glm::vec3 r)
{

	glm::mat4 rot = glm::toMat4(glm::quat(r));

	transform = glm::translate(glm::mat4(1.0), position) * rot
		* glm::scale(glm::mat4(1.0), scale);


}
glm::mat4 Plane::rotate(float degrees)
{
	transform = glm::rotate(transform, glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));
	/*glm::mat4 invert = glm::inverse(transform);
	forward = glm::normalize(glm::vec3(invert[2]));*/
	return transform;
}

glm::vec3 Plane::getForward()
{
	return forward;
}

glm::vec3 Plane::getNormal()
{
	return normal;
}

glm::mat4 Plane::getRotation()
{
	return rotation;
}
