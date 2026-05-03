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
	playerPaddle_(config_),
	aiPaddle_(config_),
	backButton_(
		Rectangle{
			100, 100, 100, 100
		},
		"Back",
		[this]()
		{
			sceneManager_->ChangeScene(SceneFactory::CreateMenu());
		}
	),
	startButton_(
		Rectangle{
			200, 100, 100, 100
		},
		"Start Game",
		[this]()
		{
			StartGame();
		}
	)
{ }

void PongGame::Init()
{
	SetWindowSize((int)config_.fieldDimension.x, (int)config_.fieldDimension.y);
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
	
	DrawLine((int)config_.fieldDimension.x / 2, 0, (int)config_.fieldDimension.x / 2, (int)config_.fieldDimension.y, config_.fieldLineColor);

	switch (state_)
	{
		case GameState::Menu:
		case GameState::GameOver:
			backButton_.Draw();
			startButton_.Draw();
			break;
		case GameState::Running:
			ball_.Draw();
			playerPaddle_.Draw();
			aiPaddle_.Draw();
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
	playerPaddle_.Init(false);
	aiPaddle_.Init(true);

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
	aiPaddle_.Move(ballPosition.y < aiPaddlePosition.y);

	if (HasBallHitPaddle())
	{
		ball_.Bounce();
	}

	ScoreWhenBallHitWall();

	ball_.Move();

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

bool PongGame::HasBallHitPaddle()
{
	Vector2 ballPosition = ball_.GetPosition();
	Vector2 aiPaddlePosition = aiPaddle_.GetPosition();
	Vector2 playerPaddlePosition = playerPaddle_.GetPosition();

	return CheckCollisionCircleRec(ballPosition, config_.ballRadius, {aiPaddlePosition.x, aiPaddlePosition.y, config_.paddleSize.x, config_.paddleSize.y}) ||
		CheckCollisionCircleRec(ballPosition, config_.ballRadius, {playerPaddlePosition.x, playerPaddlePosition.y, config_.paddleSize.x, config_.paddleSize.y});
}
