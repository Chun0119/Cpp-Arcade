#pragma once

#include <memory>

#include "scene.h"

class SceneFactory
{
public:
	static std::unique_ptr<Scene> CreateMenu();
	static std::unique_ptr<Scene> CreateSnake();
	static std::unique_ptr<Scene> CreatePong();
};