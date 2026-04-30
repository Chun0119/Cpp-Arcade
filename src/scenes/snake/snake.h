#pragma once

#include <deque>

#include "raylib.h"

class Snake
{
private:
	static constexpr float kMoveInterval = 0.1f;

	std::deque<Vector2> positions_;
	Vector2 direction_;
	bool canUpdateDirection_;
	double lastUpdateTime_;

public:
	void Draw(float cellSize);

	void Init();
	void Move();
	void Grow();

	bool IsOverlap(Vector2 objPosition);
	bool IsSelfOverlap();

	Vector2 GetHeadPosition();
	void SetDirection(Vector2 newDirection);
};