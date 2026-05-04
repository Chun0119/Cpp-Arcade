#pragma once

#include "components/button.h"

#include <string>
#include <functional>

#include "raylib.h"

class MenuGameButton : public Button
{
private:
	std::string label_;
	Texture2D texture_;

public:
	MenuGameButton(Rectangle rect, std::string assetName, std::string label, std::function<void()> onClick);

	void Draw() override;

	~MenuGameButton();
};