#include "button.h"

#include <functional>

#include "raylib.h"

Button::Button(Rectangle rect, std::function<void()> onClick) :
	rect_(rect), 
	onClick_(std::move(onClick))
{ }

Button::Button(Rectangle rect, std::function<void()> onClick, ButtonStyle style) :
	rect_(rect), 
	onClick_(std::move(onClick)), 
	style_(style)
{ }

void Button::Update()
{
	isHovered_ = CheckCollisionPointRec(GetMousePosition(), rect_);

	if (isHovered_ && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (onClick_)
		{
			onClick_();
		}
	}
}