#pragma once

#include "core/scene.h"

#include "raylib.h"

#include "components/text_button.h"

#include "snake_game_config.h"
#include "snake.h"
#include "food.h"

class SnakeGame : public Scene
{
private:
	SnakeGameConfig config_;

	enum class GameState
	{
		Menu,
		Running,
		GameOver
	};

	GameState state_ = GameState::Menu;

	Snake snake_;
	Food food_;

	int score_ = 0;
	double lastUpdateTime_ = 0.0;

	TextButton backButton_;
	TextButton startButton_;

public:
	SnakeGame();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Shutdown() override;

	void StartGame();
	void UpdateGame();
	void SpawnFood();
	bool HasSnakeEatenFood();
	bool HasSnakeHitWall();
};