#pragma once

#include <memory>

#include "scene.h"
#include "scene_manager.h"

class SceneFactory
{
public:
	static std::unique_ptr<Scene> CreateMenu(SceneManager& manager);
	static std::unique_ptr<Scene> CreateSnake();
};