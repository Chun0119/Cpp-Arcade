#pragma once

#include "raylib.h"

#include "space_invaders_config.h"

class Laser
{
private:
	const SpaceInvadersConfig* config_ = nullptr;

	Vector2 position_ = {0, 0};
	float speed_ = 0;
	bool active_ = false;

public:
	Laser() = default;
	Laser(const SpaceInvadersConfig* config, Vector2 position, float speed);

	void Draw();

	void Move();

	bool IsActive() const;
};