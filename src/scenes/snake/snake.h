#pragma once

#include <deque>

#include "raylib.h"

#include "snake_game_config.h"

class Snake
{
private:
	const SnakeGameConfig& config_;

	std::deque<Vector2> positions_;
	Vector2 direction_ = {1, 0};
	bool canUpdateDirection_ = false;

public:
	Snake() = default;
	Snake(const SnakeGameConfig& config);

	void Draw();

	void Init();
	void Move();
	void Grow();

	bool IsOverlap(Vector2 objPosition);
	bool IsSelfOverlap();
	Vector2 GetHeadNextPosition();

	void SetDirection(Vector2 newDirection);
};