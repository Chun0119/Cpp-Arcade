#include "scene_factory.h"
#include "scenes/menu.h"
#include "scenes/snake/snake.h"

// Menu needs manager injected
std::unique_ptr<Scene> SceneFactory::createMenu(SceneManager* manager) {
    return std::make_unique<Menu>(manager);
}

std::unique_ptr<Scene> SceneFactory::createSnake() {
    return std::make_unique<Snake>();
}
