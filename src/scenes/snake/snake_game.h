#pragma once

#include "core/scene.h"
#include "snake.h"
#include "food.h"

class SnakeGame : public Scene
{
private:
	static constexpr int kCellSize = 20;
	static constexpr Vector2 kCellDimension{20.0f, 20.0f};

	Snake snake_;
	Food food_;

public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Shutdown() override;
};