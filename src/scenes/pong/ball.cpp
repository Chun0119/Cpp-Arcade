#include "ball.h"

#include "raylib.h"
#include "raymath.h"

#include "pong_game_config.h"

Ball::Ball(const PongGameConfig& config) :
	config_(config)
{ }

void Ball::Draw()
{
	DrawCircle((int)position_.x, (int)position_.y, config_.ballRadius, config_.ballColor);
}

void Ball::Init(bool towardsLeft)
{
	position_ = config_.fieldDimension / 2 + config_.offset;
	direction_ = config_.ballStartDirection * (towardsLeft ? -1 : 1);
}

void Ball::Move()
{
	position_ += direction_;

	if (position_.y + config_.ballRadius >= config_.fieldDimension.y + config_.offset.y || position_.y - config_.ballRadius <= config_.offset.y)
	{
		direction_.y *= -1;
	}
}

void Ball::Bounce()
{
	direction_.x *= -1;
}

Vector2 Ball::GetPosition()
{
	return position_;
}