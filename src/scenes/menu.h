#pragma once

#include "core/scene.h"

class Menu : public Scene
{
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Shutdown() override;
};