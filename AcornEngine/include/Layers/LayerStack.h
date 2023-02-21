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
	std::vector<Layer*> layers;
	std::vector<Layer*>::iterator layerTop;
public:
	LayerStack(EntityManager* m);
	virtual ~LayerStack();

	void pushLayer(Layer* layer);
	void pushOverlay(Layer* overlay);
	void popLayer(Layer* layer);
	void popOverlay(Layer* overlay);

	void createWorldLayer(EntityManager* m);

	std::function<void(Event&)> distributeEvent();
};

#endif // LAYER_STACK_H