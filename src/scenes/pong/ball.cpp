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

	float angle = GetRandomValue(-config_.ballStartAngleRange, config_.ballStartAngleRange) * DEG2RAD; // small variation

	float dirX = cosf(angle);
	float dirY = sinf(angle);

	// force direction left/right
	dirX *= (towardsLeft ? -1.0f : 1.0f);

	direction_ = {dirX, dirY};

	// normalize + apply speed
	direction_ = Vector2Normalize(direction_) * config_.ballSpeed;
}

void Ball::Move()
{
	position_ += direction_;

	if (position_.y + config_.ballRadius >= config_.fieldDimension.y + config_.offset.y || position_.y - config_.ballRadius <= config_.offset.y)
	{
		position_.y = Clamp(
			position_.y + direction_.y,
			config_.offset.y + config_.ballRadius,
			config_.offset.y + config_.fieldDimension.y - config_.ballRadius
		);
		direction_.y *= -1;
	}
}

void Ball::Bounce(Vector2 paddlePos, Vector2 paddleSize)
{
    float paddleCenterY = paddlePos.y + paddleSize.y / 2.0f;

    float relativeIntersectY = position_.y - paddleCenterY;

    float normalized = relativeIntersectY / (paddleSize.y / 2.0f);
    normalized = Clamp(normalized, -1.0f, 1.0f);

    float maxBounceAngle = 75.0f * DEG2RAD;
    float angle = normalized * maxBounceAngle;

    float speed = Vector2Length(direction_);

    float dirX = (direction_.x > 0) ? -1.0f : 1.0f;

    direction_.x = dirX * cosf(angle) * speed;
    direction_.y = sinf(angle) * speed;

    if (dirX < 0)
    {
        // hit right paddle ? push left
        position_.x -= (position_.x + config_.ballRadius) - paddlePos.x;;
    }
    else
    {
        // hit left paddle ? push right
        position_.x += (paddlePos.x + paddleSize.x) - (position_.x - config_.ballRadius);
    }
}

Vector2 Ball::GetPosition()
{
	return position_;
}