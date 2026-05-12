#include "ufo.h"

#include "raylib.h"

#include "space_invaders_config.h"

void Ufo::SetUp(const SpaceInvadersConfig* config, const Texture2D* texture)
{
    config_ = config;
    texture_ = texture;
}

void Ufo::Spawn()
{
    bool isOnLeft = GetRandomValue(0, 1);

    float positionX = isOnLeft ? config_->offset.x : config_->offset.x + config_->fieldDimension.x - config_->spaceshipSize;
    position_ = {positionX, config_->offset.y + config_->uiPadding};

    direction_ = isOnLeft ? 1 : -1;

    active_ = true;
}

void Ufo::Draw()
{
    if (!active_)
    {
        return;
    }

    Rectangle source = {0.0f, 0.0f, (float)texture_->width, (float)texture_->height};
    Rectangle dest = {position_.x, position_.y, config_->ufoSize, config_->ufoSize};
    Vector2 origin = {0.0f, 0.0f};

    DrawTexturePro(*texture_, source, dest, origin, 0.0f, WHITE);
}

void Ufo::Move()
{
    if (!active_)
    {
        return;
    }

    position_.x += config_->ufoSpeed * direction_;

    if (position_.x < config_->offset.x || position_.x > config_->offset.x + config_->fieldDimension.x - config_->ufoSize)
    {
        active_ = false;
    }
}

bool Ufo::IsActive() const
{
    return active_;
}