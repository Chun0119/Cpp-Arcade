#include "scene_factory.h"

#include <memory>

#include "scene.h"
#include "scenes/menu.h"
#include "scenes/snake/snake_game.h"
#include "scenes/pong/pong_game.h"
#include "scenes/space_invaders/space_invaders.h"
#include "scenes/tetris/tetris.h"

// Menu needs manager injected
std::unique_ptr<Scene> SceneFactory::CreateMenu()
{
	return std::make_unique<Menu>();
}

std::unique_ptr<Scene> SceneFactory::CreateSnake()
{
	return std::make_unique<SnakeGame>();
}

std::unique_ptr<Scene> SceneFactory::CreatePong()
{
	return std::make_unique<PongGame>();
}

std::unique_ptr<Scene> SceneFactory::CreateSpaceInvaders()
{
	return std::make_unique<SpaceInvaders>();
}

std::unique_ptr<Scene> SceneFactory::CreateTetris()
{
	return std::make_unique<Tetris>();
}
