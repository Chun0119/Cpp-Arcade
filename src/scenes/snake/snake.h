#pragma once

#include <deque>

#include "raylib.h"

class Snake
{
private:
	std::deque<Vector2> positions_;
	Vector2 direction_;

public:
	void Draw();
	void MoveToDirection();
	void ChangeDirection();
	void Grow();
};