#include "Entity/Plane.h"
#include <functional>

class Button {

public:

	glm::mat4 getTransform() { return area->transform; };
	void setTransform(glm::mat4 t) { area->transform = t; };
	float x, y;
	float xLower, xUpper, yLower, yUpper;
	void updateButton(float xpos, float ypos);
	void onClick();

protected:

	using EventCallbackFn = std::function<void(Event&)>;

	Button(const EventCallbackFn& f, ScaleEvent e, glm::mat4 t, glm::vec3 pos);

	virtual void onHover() = 0;
	virtual void onUnhover() = 0;
	 
	Plane* area;
	glm::vec3 scale;

	void scaleBackground(glm::vec3 s) { scale = s; }

	
	EventCallbackFn callback;

	ScaleEvent m_event;

};

class ColorButton : Button {

public:
	ColorButton(const EventCallbackFn& f, ScaleEvent e, COLORS bColor, COLORS hColor, glm::mat4 t, glm::vec3 pos);
	void onHover() override;
	void onUnhover() override;
	COLORS getCurrentColor() { return currentColor; };
	

private:
	COLORS currentColor;
	COLORS baseColor;
	COLORS highlightColor;


};