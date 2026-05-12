#pragma once

#include "raylib.h"

#include "space_invaders_config.h"

class Ufo
{
private:
	const SpaceInvadersConfig* config_ = nullptr;
	const Texture2D* texture_ = nullptr;

	Vector2 position_ = {0, 0};
	float direction_ = 0;
	bool active_ = false;

public:
	Ufo() = default;

	void SetUp(const SpaceInvadersConfig* config, const Texture2D* texture);

	void Draw();

	void Spawn();
	void Move();

	bool IsActive() const;
};