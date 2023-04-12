#include "Entity/Entity_Impl.h"

EntityImpl::EntityImpl(ENTITY_TYPE _type, std::string _debugName, glm::vec3 pos):
	type(_type), debugName(_debugName), position(pos)
{

}

EntityImpl::~EntityImpl()
{
}