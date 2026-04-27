#pragma once

#include <memory>
#include "scene.h"

class SceneManager;

class SceneFactory {
public:
    static std::unique_ptr<Scene> createMenu(SceneManager* manager);
    static std::unique_ptr<Scene> createSnake();
};