#include "Menus/MenuFactory.h"

class MenuManager {

private:

	using EventCallbackFn = std::function<void(Event&)>;

	MenuManager();

	static MenuManager* inst;
	MenuFactory* factory;


public:

	~MenuManager();
	MenuManager(const MenuManager&) = delete;
	MenuManager& operator= (const MenuManager&) = delete;

	EventCallbackFn callback;

	std::vector<Menu*> menus;
	glm::mat4 camV;
	glm::vec3 camP;
	Menu* createEntityMenu();
	static MenuManager* instance();
	void init(const EventCallbackFn& f, glm::mat4 view, glm::vec3 pos);
	void updateCam(glm::mat4 view, glm::vec3 pos);
	float lastX, lastY;

	bool handleEvent(Event& e);
	void updateMousePositions(float xpos, float ypos) {
		lastX = xpos; lastY = ypos;
	}

	int currentID = 1;

	//Menu* createHomeMenu();
	//Menu* createEditorMenu();
	//Menu* createSimulateMenu();

};