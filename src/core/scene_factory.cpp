#include "scene_factory.h"

#include "scenes/menu.h"
#include "scenes/snake/snake_game.h"

// Menu needs manager injected
std::unique_ptr<Scene> SceneFactory::CreateMenu(SceneManager& manager)
{
	return std::make_unique<Menu>(manager);
}

std::unique_ptr<Scene> SceneFactory::CreateSnake()
{
	return std::make_unique<SnakeGame>();
}
