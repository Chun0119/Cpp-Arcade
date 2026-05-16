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

	backgroundMusic_ = LoadMusicStream("tetris/bgm.wav");
	PlayMusicStream(backgroundMusic_);

	dropSound_ = LoadSound("tetris/drop.ogg");
	clearSound_ = LoadSound("tetris/clear.ogg");
	rotateSound_ = LoadSound("tetris/rotate.ogg");
}

void Tetris::Update()
{
	UpdateMusicStream(backgroundMusic_);

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
		{
			currentTetromino_.Draw(config_.offset, false);

			Tetromino ghost = GetGhostTetromino();
			ghost.Draw(config_.offset, true);

			nextTetromino_.Draw({nextTetrominoRect.x + config_.uiPadding, nextTetrominoRect.y + config_.fontSize + config_.uiPadding * 2}, false);
			break;
		}
		case GameState::GameOver:
			currentTetromino_.Draw(config_.offset, false);
			nextTetromino_.Draw({nextTetrominoRect.x + config_.uiPadding, nextTetrominoRect.y + config_.fontSize + config_.uiPadding * 2}, false);

			std::string endingMessage = "Game Over";
			int textWidth = MeasureText(endingMessage.c_str(), config_.fontSize);

			int textX = (int)(playfieldRect.x + (playfieldRect.width - textWidth) / 2);
			int textY = (int)(playfieldRect.y + (playfieldRect.height - config_.fontSize) / 2);

			DrawRectangle(playfieldRect.x, textY - config_.uiPadding, playfieldRect.width, config_.fontSize + config_.uiPadding * 2, config_.primaryBackgroundColor);
			DrawText(endingMessage.c_str(), textX, textY, config_.fontSize, config_.primaryTextColor);

			backButton_.Draw();
			startButton_.Draw();
			break;
	}
}

void Tetris::Shutdown()
{
	UnloadMusicStream(backgroundMusic_);
	UnloadSound(dropSound_);
	UnloadSound(clearSound_);
	UnloadSound(rotateSound_);
}

void Tetris::StartGame()
{
	dropTimer_ = 0.0f;

	grid_.Init();
	currentTetromino_ = GetRandomTetromino();
	nextTetromino_ = GetRandomTetromino();

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
	
	if (IsKeyPressed(KEY_UP))
	{
		RotateCurrentTetromino();
	}

	if (IsKeyPressed(KEY_SPACE))
	{
		DropCurrentTetromino();
	}
	else
	{
		float currentDropDelay = IsKeyDown(KEY_DOWN) ? config_.tetrominoFastDropDelay : config_.tetrominoDefaultDropDelay;
		dropTimer_ += GetFrameTime();

		if (dropTimer_ < currentDropDelay)
		{
			return;
		}

		MoveTetrominoDown();
	}

	if (!grid_.IsValidPosition(currentTetromino_))
	{
		if (score_ > highScore_)
		{
			highScore_ = score_;
			SaveHighScore();
		}
		state_ = GameState::GameOver;
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

	currentTetromino_.Move(isLeft ? -1 : 1, 0);

	if (!grid_.IsValidPosition(currentTetromino_))
	{
		currentTetromino_.Move(isLeft ? 1 : -1, 0);
	}

	tetrominoMoveTimer_ = 0.0f;
}

void Tetris::RotateCurrentTetromino()
{
	int oldRotation = currentTetromino_.GetRotation();
	Cell oldPosition = currentTetromino_.GetPosition();

	currentTetromino_.Rotate();
	PlaySound(rotateSound_);

	if (grid_.IsValidPosition(currentTetromino_))
	{
		return;
	}

	// Wall kick right
	currentTetromino_.SetPosition({oldPosition.x + 1, oldPosition.y});

	if (grid_.IsValidPosition(currentTetromino_))
	{
		return;
	}

	// Wall kick left
	currentTetromino_.SetPosition({oldPosition.x - 1, oldPosition.y});

	if (grid_.IsValidPosition(currentTetromino_))
	{
		return;
	}

	// Restore
	currentTetromino_.SetPosition(oldPosition);
	currentTetromino_.SetRotation(oldRotation);
}

void Tetris::DropCurrentTetromino()
{
	while (MoveTetrominoDown())
	{
		// Keep dropping
	}

	PlaySound(dropSound_);
}

bool Tetris::MoveTetrominoDown()
{
	dropTimer_ = 0.0f;

	currentTetromino_.Move(0, 1);

	if (!grid_.IsValidPosition(currentTetromino_))
	{
		currentTetromino_.Move(0, -1);

		grid_.LockTetromino(currentTetromino_);

		int completedRow = grid_.ClearLines();
		score_ += completedRow;

		if (completedRow > 0)
		{
			PlaySound(clearSound_);
		}

		currentTetromino_ = nextTetromino_;
		nextTetromino_ = GetRandomTetromino();

		return false;
	}

	return true;
}

Tetromino Tetris::GetRandomTetromino()
{
	TetrominoType type = static_cast<TetrominoType>(GetRandomValue(0, kTetrominos.size() - 1));
	return Tetromino(&config_, type);
}

Tetromino Tetris::GetGhostTetromino()
{
	Tetromino ghost = currentTetromino_;

	while (grid_.IsValidPosition(ghost))
	{
		ghost.Move(0, 1);
	}

	ghost.Move(0, -1);

	return ghost;
}