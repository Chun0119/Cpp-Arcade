#pragma once

#include "raylib.h"

class Food
{
private:
	Vector2 position_;

public:
	void Draw(float cellSize);

	Vector2 GetPosition();
	void SetPosition(Vector2 newPosition);
};