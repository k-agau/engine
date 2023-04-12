#ifndef MENU_LAYER_H
#define MENU_LAYER_H

#include "Layer.h"
#include "Menus/MenuManager.h"


class MenuLayer : public Layer
{
public:
	MenuLayer(MenuManager* m);
	virtual ~MenuLayer();
	virtual void onAttach();
	virtual void onDetach();
	virtual void onUpdate();
	virtual bool onEvent(Event& event);

private:
	MenuManager* manager;
};

#endif // MENU_LAYER_H
