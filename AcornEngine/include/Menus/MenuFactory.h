#include "Menu.h"
#include "Events/EntityEvent.h"
#include "Events/Event.h"
#include <functional>
#include <unordered_map>

static float WIDTH = 800.0f;
static float HEIGHT = 600.0f;

class MenuFactory {
	

public:

	using EventCallbackFn = std::function<void(Event&)>;
	using EventGenerator = std::function<Event*(int, ENTITY_EVENT_MOD)>;

	MenuFactory(const EventCallbackFn& f) : cb(f) { init();  };
	~MenuFactory() = default;

	void init();

	glm::mat4 menuV;
	glm::vec3 menuP;
	std::vector<EventGenerator> buttonEventMap;
	void updateFactoryCam(glm::mat4 v, glm::vec3 p) { menuV = v; menuP = p; };

	ColorButton* makeColorButton(const EventCallbackFn& f, Event* e, COLORS b, COLORS h, glm::mat4 t, glm::vec3 pos);
	Menu* makeEntityMenu(int id);

	EventCallbackFn cb;		//callbacks
	//Menu* makeHomeMenu();
	//Menu* makeEditorMenu();
	//Menu* makeSimulateMenu();


};