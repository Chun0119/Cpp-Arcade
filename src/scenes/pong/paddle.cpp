#include "paddle.h"

#include "raylib.h"
#include "raymath.h"

#include "pong_game_config.h"

Paddle::Paddle(const PongGameConfig& config, bool isPlayer) :
	config_(config),
	isPlayer_(isPlayer)
{ }

void Paddle::Draw()
{
	DrawRectangle((int)position_.x, (int)position_.y, (int)config_.paddleSize.x, (int)config_.paddleSize.y, isPlayer_ ? config_.playerPaddleColor : config_.aiPaddleColor);
}

void Paddle::Init()
{
	float positionX = !isPlayer_ ? (config_.uiPadding + config_.offset.x) : (+config_.offset.x + config_.fieldDimension.x - config_.paddleSize.x - config_.uiPadding);
	float positionY = (config_.fieldDimension.y - config_.paddleSize.y) / 2 + config_.offset.y;
	position_ = {positionX, positionY};
}

void Paddle::Move(bool isUpward)
{
	position_.y = Clamp(position_.y + config_.paddleSpeed * (isUpward ? -1 : 1), config_.offset.y + config_.uiPadding, config_.offset.y + config_.fieldDimension.y - config_.paddleSize.y - config_.uiPadding);
}

Vector2 Paddle::GetPosition()
{
	return position_;
}