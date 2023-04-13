#ifndef WORLD_LAYER_H
#define WORLD_LAYER_H

#include "Layer.h"
#include "../Entity/EntityManager.h"
#include <vector>

class WorldLayer : public Layer
{
public:
	WorldLayer(EntityManager* m);
	~WorldLayer();
	void onAttach() override;
	void onDetach() override;
	void onUpdate() override;
	bool onEvent(Event& event) override;
	bool isEntity(EventType et) { 
		return
			et == EventType::Scale  ||
			et == EventType::Rotate ||
			et == EventType::Position;
	}

private:
	EntityManager* manager;
};

#endif // WORLD_LAYER_H