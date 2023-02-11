#include <vector>

#include "Layer.h"

class LayerStack
{
private:
	std::vector<Layer*> layers;
	std::vector<Layer*>::iterator layerTop;
public:
	LayerStack();
	~LayerStack();

	void pushLayer(Layer* layer);
	void pushOverlay(Layer* overlay);
	void popLayer(Layer* layer);
	void popOverlay(Layer* overlay);
};