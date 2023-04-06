#include "Entity/Entity.h"

class Button {

protected:
	Button(void* func());

	void onClick();
	virtual void onHover() = 0;
	virtual void onUnhover() = 0;
	 
	Plane* area;
	glm::vec3 scale;

	void scaleBackground(glm::vec3 s) { scale = s; area->applyScale(scale); }
	
	template<typename T>
	void (*onClickFunction)(T e);

};

class ColorButton : Button {

	ColorButton(void (*func)(Entity* e), glm::vec3 bColor, glm::vec3 hColor);

	void onHover() override;
	void onUnhover() override;

public:
	glm::vec3 currentColor;
	glm::vec3 baseColor;
	glm::vec3 highlightColor;


};