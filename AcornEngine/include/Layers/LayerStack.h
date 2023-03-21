#ifndef LAYER_STACK_H
#define LAYER_STACK_H

#include <vector>

#include "Layer.h"
#include "WorldLayer.h"
#include <functional>
#include <iostream>

class LayerStack
{
private:
	static LayerStack* inst;
	std::vector<Layer*> layers;
	std::vector<Layer*>::iterator layerTop;
	LayerStack();
public:
	static LayerStack* instance();

	virtual ~LayerStack();
	void pushLayer(Layer* layer);
	void pushOverlay(Layer* overlay);
	void popLayer(Layer* layer);
	void popOverlay(Layer* overlay);

	void createWorldLayer();

	std::function<void(Event&)> distributeEvent();

	std::vector<Layer*>::iterator begin();
	std::vector<Layer*>::iterator end();
};

#endif // LAYER_STACK_H