#pragma once

#include "raylib.h"

#include "space_invaders_config.h"

class Block
{
private:
	const SpaceInvadersConfig* config_ = nullptr;

	Vector2 position_ = {0, 0};

public:
	Block(const SpaceInvadersConfig* config, Vector2 position);

	void Draw();
};