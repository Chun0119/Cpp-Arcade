#pragma once

#include "raylib.h"

#include "pong_game_config.h"

class Paddle
{
private:
	const PongGameConfig& config_;
	bool isPlayer_ = false;

	Vector2 position_ = {0, 0};

public:
	Paddle() = default;
	Paddle(const PongGameConfig& config, bool isPlayer);

	void Draw();

	void Init();
	void Move(bool isUpward);

	Vector2 GetPosition();
};