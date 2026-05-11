#pragma once

#include <vector>

#include "raylib.h"

#include "laser.h"
#include "space_invaders_config.h"

class Spaceship
{
private:
	const SpaceInvadersConfig* config_ = nullptr;
	const Texture2D* texture_ = nullptr;

	Vector2 position_ = {0, 0};
	double lastFireTime_ = 0;

public:
	Spaceship() = default;

	void SetUp(const SpaceInvadersConfig* config, const Texture2D* texture);

	void Draw();

	void Init();
	void Move(bool isLeft);
	void Fire(std::vector<Laser>& lasers);
};