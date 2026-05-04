#include "grid_layout.h"

#include "raylib.h"

GridLayout::GridLayout(Vector2 start, Vector2 cellSize, float spacing, int columns) :
	start_(start),
	cellSize_(cellSize),
	spacing_(spacing),
	columns_(columns)
{ }

Rectangle GridLayout::GetCell(int index) const
{
	int row = index / columns_;
	int col = index % columns_;

	float x = start_.x + col * (cellSize_.x + spacing_);
	float y = start_.y + row * (cellSize_.y + spacing_);

	return Rectangle{x, y, cellSize_.x, cellSize_.y};
}