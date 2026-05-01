#include "scene_manager.h"

#include <memory>

#include "scene.h"

void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene)
{
	if (current_)
	{
		current_->Shutdown();
	}

	current_ = std::move(newScene);

	if (!current_)
	{
		return;
	}

	current_->SetSceneManager(this);
	current_->Init();
}

void SceneManager::Update()
{
	if (!current_)
	{
		return;
	}

	current_->Update();
}

void SceneManager::Draw()
{
	if (!current_)
	{
		return;
	}

	current_->Draw();
}