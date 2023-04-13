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
	EventType et = event.GetEventType();
	if (isEntity(et))
	{
		return manager->updateWorld(ENTITY_TYPE::CUBE, event);

	}
	else
	{
		return manager->updateWorld(ENTITY_TYPE::CAMERA, event);

	}
}