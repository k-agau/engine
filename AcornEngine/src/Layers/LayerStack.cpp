#include "Layers/LayerStack.h"
#include <algorithm>

LayerStack* LayerStack::inst = nullptr;

LayerStack* LayerStack::instance() {

	if (LayerStack::inst == nullptr) {
		LayerStack::inst = new LayerStack;
	}
	return inst;

}

LayerStack::LayerStack(): layerTop(layers.begin())
{
	createWorldLayer();
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

void LayerStack::createWorldLayer() {

	WorldLayer* wl = new WorldLayer(EntityManager::instance());
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

std::vector<Layer*>::iterator LayerStack::begin()
{
	return layers.begin();
}

std::vector<Layer*>::iterator LayerStack::end()
{
	return layers.end();
}
