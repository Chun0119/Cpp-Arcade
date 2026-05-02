#include "menu.h"

#include "raylib.h"

#include "core/scene_manager.h"
#include "core/scene_factory.h"

void Menu::Init()
{
	SetWindowSize(800, 600);
}

// update logic (input + switching scenes)
void Menu::Update()
{
	Vector2 mouse = GetMousePosition();

	Rectangle snakeGameBtn = {300, 200, 200, 50};

	if (CheckCollisionPointRec(mouse, snakeGameBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		sceneManager_->ChangeScene(SceneFactory::CreateSnake());
	}

	Rectangle pongGameBtn = {300, 410, 200, 50};

	if (CheckCollisionPointRec(mouse, pongGameBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		sceneManager_->ChangeScene(SceneFactory::CreatePong());
	}
}

// drawing
void Menu::Draw()
{
	ClearBackground(BLACK);

	DrawText("Main Menu", 320, 120, 30, WHITE);

	DrawRectangle(300, 200, 200, 50, DARKGRAY);
	DrawText("Snake Game", 340, 215, 20, WHITE);

	DrawRectangle(300, 410, 200, 50, DARKGRAY);
	DrawText("Pong Game", 340, 425, 20, WHITE);
}

void Menu::Shutdown()
{

}