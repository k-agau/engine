#include "Entity/EntityFactory.h"

#include "Entity/Cube.h"

Entity* EntityFactory::makeCube(glm::vec3 WorldCoordinates)
{
	return new Entity(new Cube("tmp",
		WorldCoordinates[0], 
		WorldCoordinates[1], 
		WorldCoordinates[2]));
}

Entity* EntityFactory::makePlane(glm::vec3 WorldCoordinates)
{
	return new Entity(new Plane("tmp",
		WorldCoordinates[0],
		WorldCoordinates[1],
		WorldCoordinates[2]));
}
