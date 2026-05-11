#include "laser.h"

#include "raylib.h"

#include "space_invaders_config.h"

Laser::Laser(const SpaceInvadersConfig* config, Vector2 position, float speed) :
    config_(config),
    position_(position),
    speed_(speed),
    active_(true)
{ }

void Laser::Draw()
{
    DrawRectangle(position_.x, position_.y, config_->laserSize.x, config_->laserSize.y, config_->laserColor);
}

void Laser::Move()
{
    position_.y += speed_;

    if (position_.y < config_->offset.y || position_.y > config_->offset.y + config_->fieldDimension.y - config_->laserSize.y)
    {
        active_ = false;
    }
}

bool Laser::IsActive() const
{
    return active_;
}