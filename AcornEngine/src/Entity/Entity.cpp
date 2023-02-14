#include "Entity/Entity.h"


Entity::Entity(EntityImpl* _bridge): bridge(_bridge)
{

}

Entity::~Entity()
{

}


EntityImpl* Entity::content()
{
	return bridge;
}