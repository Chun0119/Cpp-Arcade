#pragma once

#include <memory>

#include "scene.h"

class SceneManager
{
private:
	std::unique_ptr<Scene> current_;

public:
	void ChangeScene(std::unique_ptr<Scene> newScene);

	void Update();
	void Draw();
};