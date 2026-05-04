#pragma once

#include "core/scene.h"

#include "raylib.h"

#include "components/text_button.h"

#include "ball.h"
#include "paddle.h"
#include "pong_game_config.h"

class PongGame : public Scene
{
private:
	PongGameConfig config_;

	enum class GameState
	{
		Menu,
		Running,
		GameOver
	};

	GameState state_ = GameState::Menu;

	Ball ball_;
	Paddle playerPaddle_;
	Paddle aiPaddle_;

	int playerScore_ = 0;
	int aiScore_ = 0;

	TextButton backButton_;
	TextButton startButton_;

public:
	PongGame();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Shutdown() override;

	void StartGame();
	void UpdateGame();
	void ScoreWhenBallHitWall();

	bool HasBallHitPaddle(Vector2 paddlePosition);
};