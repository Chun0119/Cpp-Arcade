#include "snake.h"

#include <deque>

#include "raylib.h"
#include "raymath.h"

#include "snake_game_config.h"

Snake::Snake(const SnakeGameConfig& config) : 
	config_(config) 
{ }

void Snake::Draw()
{
	for (int i = 0; i < positions_.size(); i++)
	{
		Rectangle rect = Rectangle{config_.offset.x + positions_[i].x * config_.cellSize, config_.offset.y + positions_[i].y * config_.cellSize, config_.cellSize, config_.cellSize};
		DrawRectangleRounded(rect, config_.snakeRoundness, 4, i == 0 ? config_.snakeHeadColor : config_.snakeBodyColor);
	}
}

void Snake::Init()
{
	positions_.clear();

	Vector2 pos = config_.snakeStartPosition;

	for (int i = 0; i < config_.snakeStartLength; ++i)
	{
		positions_.push_back({pos.x - i, pos.y});
	}

	direction_ = config_.snakeStartDirection;
	canUpdateDirection_ = false;
}

void Snake::Move()
{
	positions_.pop_back();
	positions_.push_front(GetHeadNextPosition());
	canUpdateDirection_ = true;
}

void Snake::Grow()
{
	positions_.push_front(GetHeadNextPosition());
}

bool Snake::IsOverlap(Vector2 objPosition)
{
	for (const auto& pos : positions_)
	{
		if (Vector2Equals(pos, objPosition))
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsSelfOverlap()
{
	Vector2 head = positions_.front();
	for (size_t i = 1; i < positions_.size(); i++)
	{
		if (Vector2Equals(head, positions_[i]))
		{
			return true;
		}
	}

	return false;
}

Vector2 Snake::GetHeadNextPosition()
{
	return positions_.front() + direction_;
}

void Snake::SetDirection(Vector2 newDirection)
{
	// Make sure it's not the same direction or the opposite direction
	if (canUpdateDirection_ && Vector2Equals(direction_ * newDirection, {0, 0}))
	{
		direction_ = newDirection;
		canUpdateDirection_ = false;
	}
}