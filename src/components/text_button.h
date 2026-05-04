#pragma once

#include "button.h"

#include <string>
#include <functional>

#include "raylib.h"

class TextButton : public Button
{
private:
	std::string label_;

public:
	TextButton(Rectangle rect, std::string label, std::function<void()> onClick);
	TextButton(Rectangle rect, std::string label, std::function<void()> onClick, ButtonStyle style);

	void Draw() override;
};