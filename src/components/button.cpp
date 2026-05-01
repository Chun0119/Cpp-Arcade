#include "button.h"

#include <string>
#include <functional>

#include "raylib.h"

Button::Button(Rectangle rect, std::string label, std::function<void()> onClick) :
	rect_(rect), 
	label_(std::move(label)), 
	onClick_(std::move(onClick))
{ }

Button::Button(Rectangle rect, std::string label, std::function<void()> onClick, ButtonStyle style) :
	rect_(rect), 
	label_(std::move(label)), 
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

void Button::Draw()
{
	DrawRectangleRec(rect_, isHovered_ ? style_.hoverBackgroundColor : style_.normalBackgroundColor);

	int textWidth = MeasureText(label_.c_str(), style_.fontSize);
	int textHeight = style_.fontSize;

	float textX = rect_.x + (rect_.width - textWidth) / 2;
	float textY = rect_.y + (rect_.height - textHeight) / 2;

	DrawText(label_.c_str(), (int)textX, (int)textY, style_.fontSize, isHovered_ ? style_.hoverTextColor : style_.normalTextColor);
}

void Button::SetRect(Rectangle newRect)
{
	rect_ = newRect;
}