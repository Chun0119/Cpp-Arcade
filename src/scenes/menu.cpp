#include "menu.h"

#include "raylib.h"

#include "core/scene_factory.h"

// constructor
Menu::Menu(SceneManager& manager) : manager_(manager) {}

void Menu::Init()
{

}

// update logic (input + switching scenes)
void Menu::Update()
{
	Vector2 mouse = GetMousePosition();

	Rectangle snakeGameBtn = {300, 200, 200, 50};

	if (CheckCollisionPointRec(mouse, snakeGameBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		manager_.ChangeScene(SceneFactory::CreateSnake());
	}
}

// drawing
void Menu::Draw()
{
	DrawText("Main Menu", 320, 120, 30, WHITE);

	DrawRectangle(300, 200, 200, 50, DARKGRAY);
	DrawText("Snake Game", 340, 215, 20, WHITE);
}

void Menu::Shutdown()
{

}