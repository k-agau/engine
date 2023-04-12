#include "Button.h"
#include <vector>

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
	//			   scale    color         position
	Menu(glm::mat4 t, COLORS c, glm::vec3 p);
	~Menu();
	glm::vec3 scale;
	COLORS color;
	bool open = true;

	void addButton(Button* b) { buttons.push_back(b);  };
	std::vector<Button*>* getButtons() { return &buttons; };
	glm::mat4 getTransform() { return area->transform; };
	void setTransform(glm::mat4 t) { area->transform = t; };
};