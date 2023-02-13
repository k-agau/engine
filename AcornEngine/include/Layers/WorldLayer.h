#include "Layer.h"

#include <vector>

class WorldLayer : public Layer
{
private:
	WorldLayer() = default;
	std::vector<Layer*> worldObjects;
	static WorldLayer* inst;
public:
	static WorldLayer* instance();
	~WorldLayer();

	void onAttach() override;
	void onDetach() override;
	void onUpdate() override;
	void onEvent(Event& event) override;




};




















