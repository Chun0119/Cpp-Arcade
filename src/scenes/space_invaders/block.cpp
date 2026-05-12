#include "block.h"

#include "raylib.h"

#include "space_invaders_config.h"

Block::Block(const SpaceInvadersConfig* config, Vector2 position) :
    config_(config),
    position_(position),
    active_(true)
{ }

void Block::Draw()
{
    DrawRectangle((int)position_.x, (int)position_.y, config_->obstacleBlockSize, config_->obstacleBlockSize, config_->obstacleColor);
}

void Block::OnHit()
{
    active_ = false;
}

bool Block::IsActive() const
{
    return active_;
}

Rectangle Block::GetRect() const
{
    return {position_.x, position_.y, (float)config_->obstacleBlockSize, (float)config_->obstacleBlockSize};
}