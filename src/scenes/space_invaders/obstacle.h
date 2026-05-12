#pragma once

#include <vector>

#include "raylib.h"

#include "space_invaders_config.h"
#include "block.h"

class Obstacle
{
private:
	const SpaceInvadersConfig* config_ = nullptr;

	Vector2 position_ = {0, 0};
	std::vector<Block> blocks_;

public:
	Obstacle(const SpaceInvadersConfig* config, Vector2 position);

	void Draw();

	std::vector<Block>& GetBlocks();
};