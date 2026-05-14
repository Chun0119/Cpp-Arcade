#include "tetris.h"

#include <string>
#include <fstream>

#include "raylib.h"
#include "raymath.h"

#include "components/text_button.h"
#include "core/scene_manager.h"
#include "core/scene_factory.h"

#include "tetris_config.h"

Tetris::Tetris() :
	config_(),
	backButton_(
		Rectangle{
			(config_.offset.x + config_.fieldDimension.x / 2 - config_.buttonWidth) / 2,
			config_.offset.y + config_.fieldDimension.y + config_.uiPadding,
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
			(config_.offset.x + config_.fieldDimension.x / 2 * 3 - config_.buttonWidth) / 2,
			config_.offset.y + config_.fieldDimension.y + config_.uiPadding,
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
	Vector2 screenSize = config_.fieldDimension + config_.offset * 2;
	SetWindowSize((int)screenSize.x, (int)screenSize.y);
	SetTargetFPS(config_.targetFps);

	LoadHighScore();
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

	Rectangle playfieldRect = {config_.offset.x, config_.offset.y, config_.fieldDimension.x, config_.fieldDimension.y};
	DrawRectangleRec(playfieldRect, config_.playfieldColor);
	DrawRectangleLinesEx({playfieldRect.x - config_.playfieldBorderThickness, playfieldRect.y - config_.playfieldBorderThickness, playfieldRect.width + config_.playfieldBorderThickness * 2, playfieldRect.height + config_.playfieldBorderThickness * 2}, config_.playfieldBorderThickness, config_.secondaryBackgroundColor);

	std::string scoreText = "Score: " + std::to_string(score_);
	DrawText(scoreText.c_str(), (int)config_.offset.x + config_.uiPadding, (int)config_.offset.y - config_.uiPadding - config_.fontSize, config_.fontSize, config_.playerScoreColor);

	std::string highScoreText = "High Score: " + std::to_string(highScore_);
	int highScoreTexttWidth = MeasureText(highScoreText.c_str(), config_.fontSize);
	DrawText(highScoreText.c_str(), (int)(config_.offset.x + config_.fieldDimension.x - config_.uiPadding - highScoreTexttWidth), (int)(config_.offset.y - config_.uiPadding - config_.fontSize), config_.fontSize, config_.playerScoreColor);

	switch (state_)
	{
		case GameState::Menu:
			backButton_.Draw();
			startButton_.Draw();
			break;
		case GameState::Running:
			break;
		case GameState::GameOver:
			std::string endingMessage = "Game Over";
			int textWidth = MeasureText(endingMessage.c_str(), config_.fontSize);

			int textX = (int)(playfieldRect.x + (playfieldRect.width - textWidth) / 2);
			int textY = (int)(playfieldRect.y + (playfieldRect.height - config_.fontSize) / 2);

			DrawRectangle(0, textY - config_.uiPadding, GetScreenWidth(), config_.fontSize + config_.uiPadding * 2, config_.primaryBackgroundColor);
			DrawText(endingMessage.c_str(), textX, textY, config_.fontSize, config_.primaryTextColor);

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