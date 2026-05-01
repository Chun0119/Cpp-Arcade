#pragma once

#include "raylib.h"

#include "snake_game_config.h"

class Food
{
private:
	const SnakeGameConfig& config_;

	Vector2 position_ = {0, 0};

public:
	Food() = default;
	Food(const SnakeGameConfig& config);

	void Draw();

	Vector2 GetPosition();
	void SetPosition(Vector2 newPosition);
};