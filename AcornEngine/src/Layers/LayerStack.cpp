#include "Layers/LayerStack.h"
#include <algorithm>

LayerStack* LayerStack::inst = nullptr;

LayerStack* LayerStack::instance()
{
	if (LayerStack::inst == nullptr)
	{
		LayerStack::inst = new LayerStack();
	}

	return inst;
}

LayerStack::LayerStack(): layerTop(layers.end())
{
	createWorldLayer(EntityManager::instance());
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
		
		for (auto it = layers.rbegin(); it != layers.rend(); --it)
		{
			bool processed = (*it)->onEvent(e);
			if (processed) break;
		}
	};
}

