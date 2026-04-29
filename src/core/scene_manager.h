#pragma once

#include <memory>

class Scene; // forward declaration

class SceneManager
{
private:
	std::unique_ptr<Scene> current;

public:
	void changeScene(std::unique_ptr<Scene> newScene);

	void update();
	void draw();
};