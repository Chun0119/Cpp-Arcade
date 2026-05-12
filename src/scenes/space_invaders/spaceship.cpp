#include "spaceship.h"

#include <vector>

#include "raylib.h"
#include "raymath.h"

#include "laser.h"
#include "space_invaders_config.h"

void Spaceship::SetUp(const SpaceInvadersConfig* config, const Texture2D* texture)
{
    config_ = config;
    texture_ = texture;
}

void Spaceship::Draw()
{
    Rectangle source = { 0.0f, 0.0f, (float)texture_->width, (float)texture_->height };
    Rectangle dest = { position_.x, position_.y, config_->spaceshipSize, config_->spaceshipSize };
    Vector2 origin = {0.0f, 0.0f};

    DrawTexturePro(*texture_, source, dest, origin, 0.0f, WHITE);
}

void Spaceship::Init()
{
    position_.x = (config_->fieldDimension.x - config_->spaceshipSize) / 2 + config_->offset.x;
    position_.y = config_->offset.y + config_->fieldDimension.y - config_->spaceshipSize - config_->uiPadding;
}

void Spaceship::Move(bool isLeft)
{
	position_.x = Clamp(position_.x + config_->spaceshipSpeed * (isLeft ? -1 : 1), config_->offset.x + config_->uiPadding, config_->offset.x + config_->fieldDimension.x - config_->uiPadding - config_->spaceshipSize);
}

void Spaceship::Fire(std::vector<Laser>& lasers)
{
	double currentTime = GetTime();
	if (currentTime - lastFireTime_ < config_->spaceshipFireInterval)
	{
		return;
	}

	lastFireTime_ = currentTime;
	Vector2 laserStartPosition = {position_.x + config_->spaceshipSize / 2, position_.y};
    lasers.emplace_back(config_, laserStartPosition, -config_->laserSpeed);
}

Rectangle Spaceship::GetRect() const
{
    return {position_.x, position_.y, config_->spaceshipSize, config_->spaceshipSize};
}