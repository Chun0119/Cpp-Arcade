#include "snake_game.h"

#include "raylib.h"
#include "raymath.h"

void SnakeGame::Init()
{
	state_ = GameState::Running;
	snake_.Init();
	SpawnFood();
}

void SnakeGame::Update()
{
	if (state_ != GameState::Running)
	{
		return;
	}

	DetectInput();

	if (HasSnakeEatenFood())
	{
		snake_.Grow();
		SpawnFood();
	}
	else
	{
		snake_.Move();
	}

	if (HasSnakeHitWall() || snake_.IsSelfOverlap())
	{
		state_ = GameState::GameOver;
	}
}

void SnakeGame::Draw()
{
	snake_.Draw(kCellSize);
	food_.Draw(kCellSize);
}

void SnakeGame::Shutdown()
{

}

void SnakeGame::DetectInput()
{
	if (IsKeyPressed(KEY_UP))
	{
		snake_.SetDirection({0, -1});
	}
	else if (IsKeyPressed(KEY_DOWN))
	{
		snake_.SetDirection({0, 1});
	}
	else if (IsKeyPressed(KEY_LEFT))
	{
		snake_.SetDirection({-1, 0});
	}
	else if (IsKeyPressed(KEY_RIGHT))
	{
		snake_.SetDirection({1, 0});
	}
}

void SnakeGame::SpawnFood()
{
	Vector2 newPosition;

	do
	{
		newPosition.x = (float)GetRandomValue(0, (int)kCellDimension.x - 1);
		newPosition.y = (float)GetRandomValue(0, (int)kCellDimension.y - 1);
	} while (snake_.IsOverlap(newPosition));

	food_.SetPosition(newPosition);
}

bool SnakeGame::HasSnakeEatenFood()
{
	return Vector2Equals(food_.GetPosition(), snake_.GetHeadPosition());
}

bool SnakeGame::HasSnakeHitWall()
{
	Vector2 snakeHead = snake_.GetHeadPosition();
	return snakeHead.x < 0 || snakeHead.y < 0 || snakeHead.x > kCellDimension.x || snakeHead.y > kCellDimension.y;
}