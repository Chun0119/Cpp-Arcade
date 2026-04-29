#include "raylib.h"

#include "core/scene_manager.h"
#include "core/scene_factory.h"

int main()
{
	InitWindow(800, 600, "Cpp Arcade");

	SceneManager manager;

	manager.ChangeScene(SceneFactory::CreateMenu(manager));

	while (!WindowShouldClose())
	{
		manager.Update();

		BeginDrawing();
		ClearBackground(BLACK);

		manager.Draw();

		EndDrawing();
	}

	CloseWindow();
}