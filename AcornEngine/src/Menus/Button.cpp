#include "Menus/Button.h";

Button::Button(void* func()) :
	onClickFunction(func), area(new Plane("button", 0, 0, 0), scale(glm::vec3(1, 1, 1))
{
	scaleBackground(scale);
}

void Button::onClick()
{
	onClickFunction();
}

ColorButton::ColorButton(void (*func)(Entity* e)) :
	Button(func), baseColor(bColor), highlightColor(hColor)
{

}

void ColorButton::onHover()
{
	area->color = highlightColor;
}

void ColorButton::onUnhover()
{
	area->color = baseColor;
}