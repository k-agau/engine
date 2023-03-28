#include "Button.h"

enum MENUS {

	HOME,
	EDITOR,
	SIMULATE,
	OBJECT

};

enum JUSTIFY {

	RIGHT,
	LEFT,
	CENTER

};

class Menu {

private:

protected:
	std::vector<Button*> buttons;
	Plane* area;
	uint8_t cols = 1;
	uint8_t rows = 1;

public:
	
	Menu(glm::vec3 s, glm::vec3 c);

	glm::vec3 scale;
	glm::vec3 color;

	void addButton(Button* b) { buttons.push_back(b);  };
	std::vector<Button*>* getButtons() { return &buttons; };

};