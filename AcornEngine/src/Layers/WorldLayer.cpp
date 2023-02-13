#include "Layers/WorldLayer.h"

WorldLayer* WorldLayer::inst = nullptr;

WorldLayer* WorldLayer::instance()
{
	if (WorldLayer::inst == nullptr)
	{
		WorldLayer::inst = new WorldLayer;
	}
	return inst;
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

void WorldLayer::onEvent(Event& event)
{

}