#include "block.h"

#include "raylib.h"

#include "space_invaders_config.h"

Block::Block(const SpaceInvadersConfig* config, Vector2 position) :
    config_(config),
    position_(position)
{ }

void Block::Draw()
{
    DrawRectangle(position_.x, position_.y, config_->obstacleBlockSize, config_->obstacleBlockSize, config_->obstacleColor);
}