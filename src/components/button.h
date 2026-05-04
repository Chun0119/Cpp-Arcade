#pragma once

#include <functional>

#include "raylib.h"

struct ButtonStyle
{
	Color normalBackgroundColor = DARKGRAY;
	Color hoverBackgroundColor = GRAY;
	Color normalTextColor = WHITE;
	Color hoverTextColor = WHITE;
	int fontSize = 20;
};

class Button
{
protected:
	Rectangle rect_ = {0, 0, 0, 0};
	ButtonStyle style_;
	std::function<void()> onClick_;

	bool isHovered_ = false;

public:
	Button(Rectangle rect, std::function<void()> onClick);
	Button(Rectangle rect, std::function<void()> onClick, ButtonStyle style);

	void Update();

	virtual void Draw() = 0;
};