#pragma once

#include "core/scene.h"

#include <vector>

#include "components/grid_layout.h"

#include "menu_game_button.h"

class Menu : public Scene
{
private:
	std::vector<MenuGameButton> gameButtons_;

	GridLayout gridLayout_;

public:
	Menu();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Shutdown() override;
};