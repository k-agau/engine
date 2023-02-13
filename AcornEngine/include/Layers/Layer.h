#include <string>
#include "Event.h"

class Layer
{
protected:
	std::string layerName;
	bool enabled;
public:
	Layer(const std::string& name = "Layer");
	virtual ~Layer();
	virtual void onAttach() = 0;
	virtual void onDetach() = 0;
	virtual void onUpdate() = 0;
	virtual void onEvent(Event &event) = 0;
};