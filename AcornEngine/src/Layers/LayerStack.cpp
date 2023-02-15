#include "Layers/LayerStack.h"

#include <algorithm>

LayerStack::LayerStack(): layerTop(layers.begin())
{
}

LayerStack::~LayerStack()
{
	layers.clear();
}

void LayerStack::pushLayer(Layer* layer)
{
	layerTop = layers.emplace(layerTop, layer);
}

void LayerStack::pushOverlay(Layer* overlay)
{
	layers.emplace_back(overlay);
}

void LayerStack::popLayer(Layer* layer)
{
	auto it = std::find(layers.begin(), layers.end(), layer);
	if (it != layers.end())
	{
		layers.erase(it);
		--layerTop;
	}
}

void LayerStack::popOverlay(Layer* overlay)
{
	auto it = std::find(layers.begin(), layers.end(), overlay);
	if (it != layers.end())
	{
		layers.erase(it);
	}
}

void LayerStack::onUpdate()
{
	for (auto layer : layers)
	{
		layer->onUpdate();
	}
}

void LayerStack::onEvent(Event& event)
{
	for (auto it = layers.rbegin(); it != layers.rend() && !event.Handled; --it)
	{
		(*it)->onEvent(event);
	}
}
