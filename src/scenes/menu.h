#pragma once

#include "core/scene.h"

class SceneManager; // forward declaration

class Menu : public Scene
{
private:
	SceneManager* manager;

public:
	Menu(SceneManager* m);

	void init() override;
	void update() override;
	void draw() override;
	void shutdown() override;
};