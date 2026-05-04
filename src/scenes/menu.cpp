#include "menu.h"

#include "raylib.h"

#include "core/scene_manager.h"
#include "core/scene_factory.h"
#include "components/grid_layout.h"

#include "menu_game_button.h"

Menu::Menu() : 
    gridLayout_(
        {20, 100},   // start position
        {200, 200},   // cell size
        20.0f,        // spacing
        4             // columns
    )
{ }

void Menu::Init()
{
	SetWindowSize(900, 600);

    gameButtons_.reserve(2);

    gameButtons_.emplace_back(
        gridLayout_.GetCell(0),
        "snake.png",
        "Snake Game",
        [this]() { sceneManager_->ChangeScene(SceneFactory::CreateSnake()); }
    );

    gameButtons_.emplace_back(
        gridLayout_.GetCell(1),
        "pong.png",
        "Pong Game",
        [this]() { sceneManager_->ChangeScene(SceneFactory::CreatePong()); }
    );
}

void Menu::Update()
{
	for (auto& button : gameButtons_)
	{
		button.Update();
	}
}

// drawing
void Menu::Draw()
{
	ClearBackground({8, 12, 20, 255});

	DrawText("Main Menu", 370, 20, 30, {255, 209, 102, 255});

	for (auto& button : gameButtons_)
	{
		button.Draw();
	}
}

void Menu::Shutdown()
{
}