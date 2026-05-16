#pragma once

#include "core/scene.h"

#include "raylib.h"

#include "components/text_button.h"

#include "grid.h"
#include "tetromino.h"
#include "tetris_config.h"

class Tetris : public Scene
{
private:
	TetrisConfig config_;

	enum class GameState
	{
		Menu,
		Running,
		GameOver
	};

	GameState state_ = GameState::Menu;

	Grid grid_;

	Tetromino currentTetromino_;
	float tetrominoMoveTimer_ = 0.0f;

	Tetromino nextTetromino_;

	int score_ = 0;
	int highScore_ = 0;

	TextButton backButton_;
	TextButton startButton_;

public:
	Tetris();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Shutdown() override;

	void StartGame();
	void UpdateGame();

	void LoadHighScore();
	void SaveHighScore();

	void MoveCurrentTetromino(bool isLeft, bool isHold);

	Tetromino GetRandomTetromino();
};