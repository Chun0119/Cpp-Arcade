#include "pong_game.h"

#include <string>

#include "raylib.h"
#include "raymath.h"

#include "components/button.h"
#include "core/scene_manager.h"
#include "core/scene_factory.h"

#include "ball.h"
#include "paddle.h"
#include "pong_game_config.h"

PongGame::PongGame() :
	config_(),
	ball_(config_),
	playerPaddle_(config_, true),
	aiPaddle_(config_, false),
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
{ }

void PongGame::Init()
{
	Vector2 screenSize = config_.fieldDimension + config_.offset * 2;
	SetWindowSize((int)screenSize.x, (int)screenSize.y);
	SetTargetFPS(config_.targetFps);
}

void PongGame::Update()
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

void PongGame::Draw()
{
	ClearBackground(config_.backgroundColor);

	std::string titleText = "Pong Game";
	int titleTextWidth = MeasureText(titleText.c_str(), config_.fontSize);
	DrawText(titleText.c_str(), (GetScreenWidth() - titleTextWidth) / 2, (int)(config_.offset.y - config_.fontSize - config_.uiPadding), config_.fontSize, config_.secondaryHoverTextColor);

	DrawText(std::to_string(aiScore_).c_str(), (int)config_.offset.x + config_.uiPadding, (int)config_.offset.y - config_.uiPadding - config_.fontSize, config_.fontSize, config_.aiScoreColor);

	std::string scoreText = std::to_string(playerScore_);
	int scoreTextWidth = MeasureText(scoreText.c_str(), config_.fontSize);
	DrawText(scoreText.c_str(), (int)(config_.offset.x + config_.fieldDimension.x - config_.uiPadding - scoreTextWidth), (int)(config_.offset.y - config_.uiPadding - config_.fontSize), config_.fontSize, config_.playerScoreColor);

	Rectangle playfieldRect = {config_.offset.x, config_.offset.y, config_.fieldDimension.x, config_.fieldDimension.y};
	DrawRectangleRec(playfieldRect, config_.playfieldColor);
	DrawRectangleLinesEx({playfieldRect.x - config_.playfieldBorderThickness, playfieldRect.y - config_.playfieldBorderThickness, playfieldRect.width + config_.playfieldBorderThickness * 2, playfieldRect.height + config_.playfieldBorderThickness * 2}, config_.playfieldBorderThickness, config_.secondaryBackgroundColor);

	DrawRectangle((int)(playfieldRect.x + playfieldRect.width / 2 - config_.playfieldBorderThickness / 2), (int)config_.offset.y, (int)config_.playfieldBorderThickness, (int)playfieldRect.height, config_.fieldLineColor);

	switch (state_)
	{
		case GameState::Menu:
			backButton_.Draw();
			startButton_.Draw();
			break;
		case GameState::Running:
			ball_.Draw();
			playerPaddle_.Draw();
			aiPaddle_.Draw();
			break;
		case GameState::GameOver:
			std::string endingMessage = playerScore_ >= config_.winningScore ? "Congratulation!" : "Game Over";
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

void PongGame::Shutdown()
{

}

void PongGame::StartGame()
{
	playerScore_ = 0;
	aiScore_ = 0;

	ball_.Init(false);
	playerPaddle_.Init();
	aiPaddle_.Init();

	state_ = GameState::Running;
}

void PongGame::UpdateGame()
{
	if (IsKeyDown(KEY_UP))
	{
		playerPaddle_.Move(true);
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		playerPaddle_.Move(false);
	}

	Vector2 ballPosition = ball_.GetPosition();
	Vector2 aiPaddlePosition = aiPaddle_.GetPosition();
	Vector2 playerPaddlePosition = playerPaddle_.GetPosition();

	float paddleCenter = aiPaddlePosition.y + config_.paddleSize.y / 2;
	float diff = paddleCenter - ballPosition.y;
	if (abs(diff) > config_.paddleMoveThreshold)
	{
		aiPaddle_.Move(ballPosition.y < paddleCenter);
	}

	ball_.Move();

	if (HasBallHitPaddle(aiPaddlePosition))
	{
		ball_.Bounce(aiPaddlePosition, config_.paddleSize);
	}
	else if (HasBallHitPaddle(playerPaddlePosition))
	{
		ball_.Bounce(playerPaddlePosition, config_.paddleSize);
	}

	ScoreWhenBallHitWall();

	if (playerScore_ >= config_.winningScore || aiScore_ >= config_.winningScore)
	{
		state_ = GameState::GameOver;
	}
}

void PongGame::ScoreWhenBallHitWall()
{
	Vector2 ballPosition = ball_.GetPosition();

	if (ballPosition.x < 0)
	{
		playerScore_++;
		ball_.Init(true);
	}
	else if (ballPosition.x > config_.fieldDimension.x)
	{
		aiScore_++;
		ball_.Init(false);
	}
}

bool PongGame::HasBallHitPaddle(Vector2 paddlePosition)
{
	Vector2 ballPosition = ball_.GetPosition();
	Vector2 closest;

	closest.x = Clamp(ballPosition.x,
					  paddlePosition.x,
					  paddlePosition.x + config_.paddleSize.x);

	closest.y = Clamp(ballPosition.y,
					  paddlePosition.y,
					  paddlePosition.y + config_.paddleSize.y);

	Vector2 diff = {
		ballPosition.x - closest.x,
		ballPosition.y - closest.y
	};

	float distSq = diff.x * diff.x + diff.y * diff.y;

	return distSq <= config_.ballRadius * config_.ballRadius;
}
