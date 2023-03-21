#include "Layers/WorldLayer.h"

WorldLayer::WorldLayer(EntityManager* m) : Layer("World"), manager(m)
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
	manager->updateWorld(ENTITY_TYPE::CAMERA, event);
	return true;
}