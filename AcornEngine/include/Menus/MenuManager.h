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
	glm::vec3 currentAxis;
	std::unordered_map<int, glm::vec3> axes;
	int axisLoc;
	EventCallbackFn callback;
	bool focus;

	std::vector<Menu*> menus;
	glm::mat4 camV;
	glm::vec3 camP;
	Menu* createEntityMenu(int id);
	static MenuManager* instance();
	void init(const EventCallbackFn& f, glm::mat4 view, glm::vec3 pos);
	void updateCam(glm::mat4 view, glm::vec3 pos);
	void updateMenuPos();
	float lastX, lastY;

	bool handleEvent(Event& e);
	void updateMousePositions(float xpos, float ypos) {
		lastX = xpos; lastY = ypos;
	}
	bool open = false;
	int togglePos = 0;
	int currentID;

	//Menu* createHomeMenu();
	//Menu* createEditorMenu();
	//Menu* createSimulateMenu();

};