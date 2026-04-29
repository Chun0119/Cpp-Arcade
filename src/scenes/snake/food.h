#pragma once

#include "raylib.h"

class Food
{
private:
	Vector2 position_;

public:
	void Draw();
	void ChangePosition();
};