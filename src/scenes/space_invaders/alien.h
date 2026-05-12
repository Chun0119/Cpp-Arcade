#pragma once

#include <vector>

#include "raylib.h"

#include "laser.h"
#include "space_invaders_config.h"

class Alien
{
private:
	const SpaceInvadersConfig* config_ = nullptr;
	const Texture2D* texture_ = nullptr;

	Vector2 position_ = {0, 0};
	bool active_ = false;

public:
	Alien(const SpaceInvadersConfig* config, const Texture2D* texture, Vector2 position);

	void Draw();

	void Move(bool isLeft);
	void MoveDown();
	void Fire(std::vector<Laser>& lasers);
	void OnHit();

	bool IsActive() const;
	bool IsOutOfField() const;
	Rectangle GetRect() const;
};