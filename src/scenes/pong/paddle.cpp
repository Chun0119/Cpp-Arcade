#include "paddle.h"

#include "raylib.h"
#include "raymath.h"

#include "pong_game_config.h"

Paddle::Paddle(const PongGameConfig& config) :
	config_(config)
{ }

void Paddle::Draw()
{
	DrawRectangle((int)position_.x, (int)position_.y, (int)config_.paddleSize.x, (int)config_.paddleSize.y, config_.paddleColor);
}

void Paddle::Init(bool isLeft)
{
	float positionX = isLeft ? config_.uiPadding : (config_.fieldDimension.x - config_.paddleSize.x - config_.uiPadding);
	position_ = {positionX, (config_.fieldDimension.y - config_.paddleSize.y) / 2};
}

void Paddle::Move(bool isUpward)
{
	position_.y = Clamp(position_.y + config_.paddleSpeed * (isUpward ? -1 : 1), config_.uiPadding, config_.fieldDimension.y - config_.paddleSize.y - config_.uiPadding);
}

Vector2 Paddle::GetPosition()
{
	return position_;
}