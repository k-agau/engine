#include "Menu.h"
#include "Events/EntityEvent.h"
#include "Events/Event.h"


class MenuFactory {
	

public:

	using EventCallbackFn = std::function<void(Event&)>;

	MenuFactory(const EventCallbackFn& f) : 
		cb(f) 
	{};
	~MenuFactory() = default;

	glm::mat4 menuV;
	glm::vec3 menuP;
	void updateFactoryCam(glm::mat4 v, glm::vec3 p) { menuV = v; menuP = p; };

	ColorButton* makeColorButton(const EventCallbackFn& f, Event e, COLORS b, COLORS h, glm::mat4 t, glm::vec3 pos);
	Menu* makeEntityMenu();

	EventCallbackFn cb;		//callbacks
	//Menu* makeHomeMenu();
	//Menu* makeEditorMenu();
	//Menu* makeSimulateMenu();


};