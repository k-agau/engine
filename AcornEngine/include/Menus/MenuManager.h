#include "Menus/MenuFactory.h"

class MenuManager {

private:

	MenuManager();
	static MenuManager* inst;
	MenuFactory* factory;

public:
	
	~MenuManager();
	MenuManager(const MenuManager&) = delete;
	MenuManager& operator= (const MenuManager&) = delete;

	std::vector<Menu*> menus;
	Menu* createEntityMenu(Entity* entity);
	static MenuManager* instance();
	//Menu* createHomeMenu();
	//Menu* createEditorMenu();
	//Menu* createSimulateMenu();

};