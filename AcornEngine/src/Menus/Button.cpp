#include "Menus/Button.h";

Button::Button(const EventCallbackFn& f,ScaleEvent e, glm::mat4 t, glm::vec3 pos) :
	callback(f),
	m_event (e),
	area(new Plane("button", pos)), 
	scale(glm::vec3(0.04, 0.04, 0.04))
{
	//t[3][0] = 0.0f; t[3][1] = 0.0f; t[3][2] = 0.0f; 
	
	area->transform = t;
	area->transform = glm::scale(area->transform, scale);
}

void Button::onClick()
{
	callback(m_event);
	onHover();
}

void Button::updateButton(float xpos, float ypos)
{
	if (xpos >= xLower && xpos <= xUpper && ypos >= yLower && ypos <= yUpper) {
		onHover();
	}
	else
	{
		onUnhover();
	}
}

ColorButton::ColorButton(const EventCallbackFn& f, ScaleEvent e, COLORS bColor, COLORS hColor, glm::mat4 t, glm::vec3 pos) :
	Button(f,e,t,pos), 
	baseColor(bColor),
	highlightColor(hColor), 
	currentColor(bColor)
{

}

void ColorButton::onHover()
{
	currentColor = highlightColor;
}

void ColorButton::onUnhover()
{
	currentColor = baseColor;
}