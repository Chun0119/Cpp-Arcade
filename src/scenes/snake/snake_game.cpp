#include "snake_game.h"

#include <string>

#include "raylib.h"
#include "raymath.h"

#include "components/button.h"
#include "core/scene_manager.h"
#include "core/scene_factory.h"

#include "snake.h"
#include "food.h"

SnakeGame::SnakeGame() : 
	config_(),
    snake_(config_),
    food_(config_),
	backButton_(
		Rectangle{
			config_.offset.x,
			config_.offset.y + config_.cellDimension.y * config_.cellSize + config_.uiPadding,
			config_.buttonWidth,
			config_.buttonHeight
		},
		"Back",
		[this]()
		{
			sceneManager_->ChangeScene(SceneFactory::CreateMenu());
		},
		ButtonStyle {
			config_.secondaryBackgroundColor,
			config_.secondaryHoverBackgroundColor,
			config_.secondaryTextColor,
			config_.secondaryHoverTextColor,
			config_.fontSize
		}
	),
	startButton_(
		Rectangle{
			config_.offset.x + config_.cellDimension.y * config_.cellSize / 2,
			config_.offset.y + config_.cellDimension.y * config_.cellSize + config_.uiPadding,
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
{}

void SnakeGame::Init()
{
	Vector2 screenSize = config_.cellDimension * config_.cellSize + config_.offset * 2;
	SetWindowSize((int)screenSize.x, (int)screenSize.y);
}

void SnakeGame::Update()
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

void SnakeGame::Draw()
{
	ClearBackground(config_.backgroundColor);

	DrawText("Snake Game", (int)config_.offset.x, (int)(config_.offset.y - config_.fontSize - config_.uiPadding), config_.fontSize, config_.secondaryHoverTextColor);
	
	std::string scoreText = "Score: " + std::to_string(score_);
	int textWidth = MeasureText(scoreText.c_str(), config_.fontSize);
	DrawText(scoreText.c_str(), (int)(config_.offset.x + config_.cellDimension.x * config_.cellSize - textWidth), (int)(config_.offset.y - config_.fontSize - config_.uiPadding), config_.fontSize, config_.secondaryHoverTextColor);

	Rectangle playfieldRect = {config_.offset.x, config_.offset.y, config_.cellDimension.x * config_.cellSize, config_.cellDimension.y * config_.cellSize};
	DrawRectangleRec(playfieldRect, config_.playfieldColor);
	DrawRectangleLinesEx({playfieldRect.x - config_.playfieldBorderThickness, playfieldRect.y - config_.playfieldBorderThickness, playfieldRect.width + config_.playfieldBorderThickness * 2, playfieldRect.height + config_.playfieldBorderThickness * 2}, config_.playfieldBorderThickness, config_.secondaryBackgroundColor);

	switch (state_)
	{
		case GameState::Menu:
			backButton_.Draw();
			startButton_.Draw();
			break;
		case GameState::Running:
			snake_.Draw();
			food_.Draw();
			break;
		case GameState::GameOver:
			snake_.Draw();
			food_.Draw();
			backButton_.Draw();
			startButton_.Draw();
			break;
	}
}

void SnakeGame::Shutdown()
{

}

void SnakeGame::StartGame()
{
	score_ = 0;
	snake_.Init();
	SpawnFood();

	state_ = GameState::Running;
}

void SnakeGame::UpdateGame()
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

	double currentTime = GetTime();
	if (currentTime - lastUpdateTime_ < config_.moveDelaySeconds)
	{
		return;
	}

	lastUpdateTime_ = currentTime;
	if (HasSnakeHitWall() || snake_.IsSelfOverlap())
	{
		state_ = GameState::GameOver;
		return;
	}

	if (HasSnakeEatenFood())
	{
		score_++;
		snake_.Grow();
		SpawnFood();
	}
	else
	{
		snake_.Move();
	}
}

void SnakeGame::SpawnFood()
{
	Vector2 newPosition;

	do
	{
		newPosition.x = (float)GetRandomValue(0, (int)config_.cellDimension.x - 1);
		newPosition.y = (float)GetRandomValue(0, (int)config_.cellDimension.y - 1);
	} while (snake_.IsOverlap(newPosition));

	food_.SetPosition(newPosition);
}

bool SnakeGame::HasSnakeEatenFood()
{
	return Vector2Equals(food_.GetPosition(), snake_.GetHeadNextPosition());
}

bool SnakeGame::HasSnakeHitWall()
{
	Vector2 snakeHead = snake_.GetHeadNextPosition();
	return snakeHead.x < 0 || snakeHead.y < 0 || snakeHead.x >= config_.cellDimension.x || snakeHead.y >= config_.cellDimension.y;
}