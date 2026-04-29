#pragma once

#include "core/scene.h"
#include "core/scene_manager.h"

class Menu : public Scene
{
private:
	SceneManager& manager_;

public:
	Menu(SceneManager& manager);

	void Init() override;
	void Update() override;
	void Draw() override;
	void Shutdown() override;
};