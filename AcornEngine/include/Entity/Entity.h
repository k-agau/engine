#ifndef ENTITY_H
#define ENTITY_H

#include "Entity/Entity_Impl.h"

class Entity
{
private:
	EntityImpl* bridge;
	bool canCollide;
public:

	Entity(EntityImpl* _bridge);
	~Entity();
	EntityImpl* content();
};

#endif // ENTITY_H