#ifndef WORLD_LAYER_H
#define WORLD_LAYER_H

#include "Layer.h"
#include <vector>

class WorldLayer : public Layer
{
public:
	WorldLayer();
	~WorldLayer();
	void onAttach() override;
	void onDetach() override;
	void onUpdate() override;
	void onEvent(Event& event) override;
};

#endif // WORLD_LAYER_H