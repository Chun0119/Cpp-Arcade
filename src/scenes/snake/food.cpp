#include "food.h"

#include "raylib.h"

Food::Food(const SnakeGameConfig& config) : 
	config_(config) 
{ }

void Food::Draw()
{
	float radius = config_.cellSize * config_.foodRadiusScale;
	int centerX = (int)(config_.offset.x + position_.x * config_.cellSize + config_.cellSize / 2.0f);
	int centerY = (int)(config_.offset.y + position_.y * config_.cellSize + config_.cellSize / 2.0f);

	DrawCircle(centerX, centerY, radius, config_.foodColor);
	DrawCircle(centerX, centerY, radius * config_.foodGlowRadiusMultiplier, config_.foodGlowColor);
}

Vector2 Food::GetPosition()
{
	return position_;
}

void Food::SetPosition(Vector2 newPosition)
{
	position_ = newPosition;
}
