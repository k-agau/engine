#include "Entity/EntityFactory.h"

#include "Entity/Cube.h"

Entity EntityFactory::makeCube()
{
	return Entity(new Cube("tmp", 1, 2, 3));
}
