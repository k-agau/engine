#include "Layers/WorldLayer.h"

WorldLayer::WorldLayer(EntityManager* m) : manager(m)
{

}

WorldLayer::~WorldLayer()
{

}

void WorldLayer::onAttach()
{

}

void WorldLayer::onDetach()
{

}

void WorldLayer::onUpdate()
{

}

bool WorldLayer::onEvent(Event& event)
{
	manager->updateWorld(Entity_Type::CAMERA, event);
	return true;
}