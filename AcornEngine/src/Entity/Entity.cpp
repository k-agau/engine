#include "Entity/Entity.h"


Entity::Entity(EntityImpl* _bridge): bridge(_bridge)
{

}

Entity::~Entity()
{
	bridge = nullptr;
}


EntityImpl* Entity::content()
{
	return bridge;
}