#include "raylib.h"
#include "core/scene_manager.h"
#include "core/scene_factory.h"

int main()
{
	InitWindow(800, 600, "Cpp Arcade");

	SceneManager manager;

	manager.changeScene(SceneFactory::createMenu(&manager));

	while (!WindowShouldClose())
	{
		manager.update();

		BeginDrawing();
		ClearBackground(BLACK);

		manager.draw();

		EndDrawing();
	}

	CloseWindow();
}