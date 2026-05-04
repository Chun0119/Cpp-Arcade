#include "text_button.h"

#include <string>
#include <functional>

#include "raylib.h"

TextButton::TextButton(Rectangle rect, std::string label, std::function<void()> onClick) :
	label_(std::move(label)),
	Button(rect, onClick)
{ }

TextButton::TextButton(Rectangle rect, std::string label, std::function<void()> onClick, ButtonStyle style) :
	label_(std::move(label)),
	Button(rect, onClick, style)
{ }

void TextButton::Draw()
{
	DrawRectangleRec(rect_, isHovered_ ? style_.hoverBackgroundColor : style_.normalBackgroundColor);

	int textWidth = MeasureText(label_.c_str(), style_.fontSize);
	int textHeight = style_.fontSize;

	float textX = rect_.x + (rect_.width - textWidth) / 2;
	float textY = rect_.y + (rect_.height - textHeight) / 2;

	DrawText(label_.c_str(), (int)textX, (int)textY, style_.fontSize, isHovered_ ? style_.hoverTextColor : style_.normalTextColor);
}