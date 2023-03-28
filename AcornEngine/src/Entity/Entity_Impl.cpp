#include "Entity/Entity_Impl.h"

EntityImpl::EntityImpl(ENTITY_TYPE _type, std::string _debugName, uint8_t _x, uint8_t _y, uint8_t _z, bool physics) :
	type(_type), debugName(_debugName), position(glm::vec3(_x, _y, _z)), applyPhysics(physics), 
	rotation(glm::vec3(1, 1, 1)), scale(glm::vec3(1, 1, 1))
{

}

EntityImpl::~EntityImpl()
{
}