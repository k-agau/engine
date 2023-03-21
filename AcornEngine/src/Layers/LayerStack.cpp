#include "Layers/LayerStack.h"
#include <algorithm>

LayerStack::LayerStack(EntityManager* m): layerTop(layers.begin())
{
	createWorldLayer(m);
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

void LayerStack::createWorldLayer(EntityManager* m) {

	WorldLayer* wl = new WorldLayer(m);
	pushLayer(wl);

}

std::function<void(Event&e)> LayerStack::distributeEvent() {

	return [this](Event& e) {
		
		for (auto& l : layers) 
		{
			bool processed = l->onEvent(e);
			if (processed) break;

		}

	};
}

