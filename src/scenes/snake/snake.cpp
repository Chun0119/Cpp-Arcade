#include "snake.h"

#include "raylib.h"
#include "raymath.h"

void Snake::Draw(float cellSize)
{
	for (int i = 0; i < positions_.size(); i++)
	{
		Rectangle rect = Rectangle{positions_[i].x * cellSize, positions_[i].y * cellSize, cellSize, cellSize};
		DrawRectangleRounded(rect, 0.5, 6, WHITE);
	}
}

void Snake::Init()
{
	positions_.clear();

	positions_.push_back({5, 5});
	positions_.push_back({4, 5});
	positions_.push_back({3, 5});

	direction_ = {1, 0};

	canUpdateDirection_ = false;
}

void Snake::Move()
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime_ >= kMoveInterval)
	{
		lastUpdateTime_ = currentTime;
		positions_.pop_back();
		positions_.push_front(positions_.front() + direction_);
		canUpdateDirection_ = true;
	}
}

void Snake::Grow()
{
	positions_.push_front(positions_.front() + direction_);
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
	Vector2 head = GetHeadPosition();
	for (size_t i = 1; i < positions_.size(); i++)
	{
		if (Vector2Equals(head, positions_[i]))
		{
			return true;
		}
	}

	return false;
}

Vector2 Snake::GetHeadPosition()
{
	return positions_.front();
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