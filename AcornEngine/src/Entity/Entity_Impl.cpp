#include "Entity/Entity_Impl.h"

EntityImpl::EntityImpl(Entity_Type _type, std::string _debugName, uint8_t _x, uint8_t _y, uint8_t _z):
	type(_type), debugName(_debugName), x(_x), y(_y), z(_z)
{

}

EntityImpl::~EntityImpl()
{
}