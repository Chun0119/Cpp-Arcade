#include "obstacle.h"

#include "raylib.h"

#include "space_invaders_config.h"
#include "block.h"

Obstacle::Obstacle(const SpaceInvadersConfig* config, Vector2 position) :
    config_(config),
    position_(position)
{
    for (int row = 0; row < config_->obstacleShape.size(); ++row)
    {
        for (int column = 0; column < config_->obstacleShape[0].size(); ++column)
        {
            if (config_->obstacleShape[row][column] == 1)
            {
                blocks_.emplace_back(config, Vector2{position_.x + column * config_->obstacleBlockSize, position_.y + row * config_->obstacleBlockSize});
            }
        }
    }
}

void Obstacle::Draw()
{
    for (auto& block : blocks_)
    {
        block.Draw();
    }
}

std::vector<Block>& Obstacle::GetBlocks()
{
    return blocks_;
}