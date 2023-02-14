#include "Entity/Entity.h"

class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();
	Entity makeCube();
};