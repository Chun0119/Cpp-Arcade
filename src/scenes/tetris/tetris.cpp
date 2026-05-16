#include "tetris.h"

#include <string>
#include <fstream>

#include "raylib.h"
#include "raymath.h"

#include "components/text_button.h"
#include "core/scene_manager.h"
#include "core/scene_factory.h"

#include "grid.h"
#include "tetromino.h"
#include "tetris_config.h"
#include "tetromino_config.h"

Tetris::Tetris() :
	config_(),
	grid_(config_),
	backButton_(
		Rectangle{
			config_.offset.x + config_.gridColumn * config_.tetrominoCellSize + (config_.panelWidth - config_.buttonWidth) / 2,
			config_.offset.y + config_.gridRow * config_.tetrominoCellSize - (config_.uiPadding + config_.buttonHeight) * 2,
			config_.buttonWidth,
			config_.buttonHeight
		},
		"Back",
		[this]()
		{
			sceneManager_->ChangeScene(SceneFactory::CreateMenu());
		},
		ButtonStyle{
			config_.secondaryBackgroundColor,
			config_.secondaryHoverBackgroundColor,
			config_.secondaryTextColor,
			config_.secondaryHoverTextColor,
			config_.fontSize
		}
	),
	startButton_(
		Rectangle{
			config_.offset.x + config_.gridColumn * config_.tetrominoCellSize + (config_.panelWidth - config_.buttonWidth) / 2,
			config_.offset.y + config_.gridRow * config_.tetrominoCellSize - config_.uiPadding - config_.buttonHeight,
			config_.buttonWidth,
			config_.buttonHeight
		},
		"Start Game",
		[this]()
		{
			StartGame();
		},
		ButtonStyle{
			config_.primaryBackgroundColor,
			config_.primaryHoverBackgroundColor,
			config_.primaryTextColor,
			config_.primaryHoverTextColor,
			config_.fontSize
		}
	)
{
}

void Tetris::Init()
{
	int screenSizeX = config_.gridColumn * config_.tetrominoCellSize + config_.panelWidth + config_.offset.x * 2;
	int screenSizeY = config_.gridRow * config_.tetrominoCellSize + config_.offset.y * 2;
	SetWindowSize(screenSizeX, screenSizeY);
	SetTargetFPS(config_.targetFps);

	LoadHighScore();

	grid_.Init();
	currentTetromino_ = GetRandomTetromino();
	nextTetromino_ = GetRandomTetromino();
}

void Tetris::Update()
{
	switch (state_)
	{
		case GameState::Menu:
		case GameState::GameOver:
			backButton_.Update();
			startButton_.Update();
			break;
		case GameState::Running:
			UpdateGame();
			break;
	}
}

void Tetris::Draw()
{
	ClearBackground(config_.backgroundColor);

	std::string titleText = "Tetris";
	int titleTextWidth = MeasureText(titleText.c_str(), config_.fontSize);
	DrawText(titleText.c_str(), (GetScreenWidth() - titleTextWidth) / 2, (int)(config_.offset.y - config_.fontSize - config_.uiPadding), config_.fontSize, config_.secondaryHoverTextColor);

	Rectangle playfieldRect = {config_.offset.x, config_.offset.y,config_.gridColumn * config_.tetrominoCellSize, config_.gridRow * config_.tetrominoCellSize};
	DrawRectangleRec(playfieldRect, config_.gridLineColor);
	DrawRectangleLinesEx({playfieldRect.x - config_.playfieldBorderThickness, playfieldRect.y - config_.playfieldBorderThickness, playfieldRect.width + config_.playfieldBorderThickness * 2, playfieldRect.height + config_.playfieldBorderThickness * 2}, config_.playfieldBorderThickness, config_.secondaryBackgroundColor);

	Rectangle nextTetrominoRect = {playfieldRect.x + playfieldRect.width + config_.uiPadding, config_.offset.y, config_.panelWidth - config_.uiPadding * 2, config_.uiPadding * 3 + config_.tetrominoCellSize * 4 + config_.fontSize};
	DrawRectangleRec(nextTetrominoRect, config_.panelColor);
	DrawText("Next", nextTetrominoRect.x + config_.uiPadding, nextTetrominoRect.y + config_.uiPadding, config_.fontSize, config_.uiLabelColor);

	Rectangle scoreRect = {nextTetrominoRect.x, nextTetrominoRect.y + nextTetrominoRect.height + config_.uiPadding, nextTetrominoRect.width, config_.fontSize + config_.uiPadding * 2};
	DrawRectangleRec(scoreRect, config_.panelColor);
	std::string scoreText = "Score: " + std::to_string(score_);
	DrawText(scoreText.c_str(), scoreRect.x + config_.uiPadding, scoreRect.y + config_.uiPadding, config_.fontSize, config_.playerScoreColor);

	Rectangle highScoreRect = {scoreRect.x, scoreRect.y + scoreRect.height + config_.uiPadding, scoreRect.width, config_.fontSize + config_.uiPadding * 2};
	DrawRectangleRec(highScoreRect, config_.panelColor);
	std::string highScoreText = "High Score: " + std::to_string(highScore_);
	DrawText(highScoreText.c_str(), highScoreRect.x + config_.uiPadding, highScoreRect.y + config_.uiPadding, config_.fontSize, config_.playerScoreColor);

	grid_.Draw();

	switch (state_)
	{
		case GameState::Menu:
			backButton_.Draw();
			startButton_.Draw();
			break;
		case GameState::Running:
			currentTetromino_.Draw(config_.offset);
			nextTetromino_.Draw({nextTetrominoRect.x + config_.uiPadding, nextTetrominoRect.y + config_.fontSize + config_.uiPadding * 2});
			break;
		case GameState::GameOver:
			backButton_.Draw();
			startButton_.Draw();
			break;
	}
}

void Tetris::Shutdown()
{
}

void Tetris::StartGame()
{
	score_ = 0;

	state_ = GameState::Running;
}

void Tetris::UpdateGame()
{
	if (IsKeyPressed(KEY_LEFT))
	{
		MoveCurrentTetromino(true, false);
	}
	else if (IsKeyPressed(KEY_RIGHT))
	{
		MoveCurrentTetromino(false, false);
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		MoveCurrentTetromino(true, true);
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		MoveCurrentTetromino(false, true);
	}
	
	if (IsKeyPressed(KEY_SPACE))
	{
		currentTetromino_.Rotate();
	}
}

void Tetris::LoadHighScore()
{
	highScore_ = 0;
	std::ifstream highScoreFile(config_.highScoreFileName);
	if (highScoreFile.is_open())
	{
		highScoreFile >> highScore_;
		highScoreFile.close();
	}
}

void Tetris::SaveHighScore()
{
	std::ofstream highScoreFile(config_.highScoreFileName);
	if (highScoreFile.is_open())
	{
		highScoreFile << highScore_;
		highScoreFile.close();
	}
}

void Tetris::MoveCurrentTetromino(bool isLeft, bool isHold)
{
	if (isHold)
	{
		tetrominoMoveTimer_ += GetFrameTime();

		if (tetrominoMoveTimer_ < config_.tetrominoMoveInterval)
		{
			return;
		}
	}

	currentTetromino_.Move(isLeft);
	tetrominoMoveTimer_ = 0.0f;
}

Tetromino Tetris::GetRandomTetromino()
{
	TetrominoType type = static_cast<TetrominoType>(GetRandomValue(0, kTetrominos.size() - 1));
	return Tetromino(&config_, type);
}