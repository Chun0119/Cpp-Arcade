#include "menu_game_button.h"

#include <string>
#include <functional>

#include "raylib.h"

MenuGameButton::MenuGameButton(Rectangle rect, std::string assetName, std::string label, std::function<void()> onClick) :
	label_(std::move(label)),
	Button(rect, onClick, {
		{17, 27, 46, 255},
		{28, 42, 70, 255},
		{230, 237, 243, 255},
		{255, 255, 255, 255},
		20
	})
{ 
	texture_ = LoadTexture(assetName.c_str());
}

void MenuGameButton::Draw()
{
	DrawRectangleRec(rect_, isHovered_ ? style_.hoverBackgroundColor : style_.normalBackgroundColor);

	// reserve top 70% for texture
	float textureAreaHeight = rect_.height * 0.7f;

	// scale texture to fit width
	float scale = textureAreaHeight / texture_.height;

	float texWidth = texture_.width * scale;

	// center horizontally
	float texX = rect_.x + (rect_.width - texWidth) / 2;
	float texY = rect_.y + 5;

	DrawTextureEx(texture_, {texX, texY}, 0.0f, scale, WHITE);

	int textWidth = MeasureText(label_.c_str(), style_.fontSize);
	int textHeight = style_.fontSize;

	// define bottom 30% area
	float textAreaY = rect_.y + rect_.height * 0.7f;
	float textAreaHeight = rect_.height * 0.3f;

	// center text inside that area
	float textX = rect_.x + (rect_.width - textWidth) / 2;
	float textY = textAreaY + (textAreaHeight - textHeight) / 2;

	DrawText(label_.c_str(), (int)textX, (int)textY, style_.fontSize, isHovered_ ? style_.hoverTextColor : style_.normalTextColor);
}

MenuGameButton::~MenuGameButton()
{
	UnloadTexture(texture_);
}
