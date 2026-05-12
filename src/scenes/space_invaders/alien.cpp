#include "alien.h"

#include <vector>

#include "raylib.h"
#include "raymath.h"

#include "laser.h"
#include "space_invaders_config.h"

Alien::Alien(const SpaceInvadersConfig* config, const Texture2D* texture, Vector2 position) : 
    config_(config),
    texture_(texture),
    position_(position)
{ }

void Alien::Draw()
{
    Rectangle source = {0.0f, 0.0f, (float)texture_->width, (float)texture_->height};
    Rectangle dest = {position_.x, position_.y, config_->alienSize, config_->alienSize};
    Vector2 origin = {0.0f, 0.0f};

    DrawTexturePro(*texture_, source, dest, origin, 0.0f, WHITE);
}

void Alien::Move(bool isLeft)
{
    position_.x += config_->alienSpeed.x * (isLeft ? -1 : 1);
}

void Alien::MoveDown()
{
    position_.y += config_->alienSpeed.y;
}

void Alien::Fire(std::vector<Laser>& lasers)
{
    Vector2 laserStartPosition = {position_.x + config_->alienSize / 2, position_.y + config_->alienSize};
    lasers.emplace_back(config_, laserStartPosition, config_->laserSpeed);
}

bool Alien::IsOutOfField() const
{
    return position_.x < config_->offset.x || position_.x > config_->offset.x + config_->fieldDimension.x - config_->alienSize;
}