#include "Menu.h"

class MenuFactory {
	
public:
	MenuFactory() = default;
	~MenuFactory() = default;

	ColorButton* makeColorButton(void* func());
	Menu* makeEntityMenu(Entity* entity);
	//Menu* makeHomeMenu();
	//Menu* makeEditorMenu();
	//Menu* makeSimulateMenu();


};