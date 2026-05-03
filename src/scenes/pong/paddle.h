#pragma once

#include "raylib.h"

#include "pong_game_config.h"

class Paddle
{
private:
	const PongGameConfig& config_;

	Vector2 position_ = {0, 0};

public:
	Paddle() = default;
	Paddle(const PongGameConfig& config);

	void Draw();

	void Init(bool isLeft);
	void Move(bool isUpward);

	Vector2 GetPosition();
};