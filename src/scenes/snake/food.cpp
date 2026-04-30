#include "food.h"

#include "raylib.h"

void Food::Draw(float cellSize)
{
	Rectangle rect = Rectangle{position_.x * cellSize, position_.y * cellSize, cellSize, cellSize};
	DrawRectangleRounded(rect, 0.5, 6, WHITE);
}

Vector2 Food::GetPosition()
{
	return position_;
}

void Food::SetPosition(Vector2 newPosition)
{
	position_ = newPosition;
}
