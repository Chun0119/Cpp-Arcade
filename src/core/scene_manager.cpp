#include "scene_manager.h"
#include "scene.h"

void SceneManager::changeScene(std::unique_ptr<Scene> newScene)
{
	if (current)
	{
		current->shutdown();
	}

	current = std::move(newScene);

	if (!current)
	{
		return;
	}

	current->init();
}

void SceneManager::update()
{
	if (!current)
	{
		return;
	}

	current->update();
}

void SceneManager::draw()
{
	if (!current)
	{
		return;
	}

	current->draw();
}