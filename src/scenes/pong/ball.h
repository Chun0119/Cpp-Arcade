#pragma once

#include "raylib.h"

#include "pong_game_config.h"

class Ball
{
private:
	const PongGameConfig& config_;

	Vector2 position_ = {0, 0};
	Vector2 direction_ = {0, 0};

public:
	Ball() = default;
	Ball(const PongGameConfig& config);

	void Draw();

	void Init(bool towardsLeft);
	void Move();
	void Bounce();

	Vector2 GetPosition();
};