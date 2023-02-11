#include "LayerStack.h"

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
	layers.emplace_back(overlay)
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
