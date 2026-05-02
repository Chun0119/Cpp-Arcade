#include "pong_game.h"

#include <string>

#include "raylib.h"
#include "raymath.h"

#include "components/button.h"
#include "core/scene_manager.h"
#include "core/scene_factory.h"

PongGame::PongGame() :
	config_(),
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
	SetWindowSize(1200, 800);
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
	ClearBackground(BLACK);

	switch (state_)
	{
		case GameState::Menu:
			backButton_.Draw();
			startButton_.Draw();
			break;
		case GameState::Running:
			break;
		case GameState::GameOver:
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
	score_ = 0;

	state_ = GameState::Running;
}

void PongGame::UpdateGame()
{
}
