#ifndef MENU_LAYER_H
#define MENU_LAYER_H

#include "Layer.h"

class MenuLayer : public Layer
{
public:
	MenuLayer();
	virtual ~MenuLayer();
	virtual void onAttach();
	virtual void onDetach();
	virtual void onUpdate();
	virtual void onEvent(Event& event);
};

#endif // MENU_LAYER_H
