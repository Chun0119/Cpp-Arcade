#include "space_invaders.h"

#include <string>

#include "raylib.h"
#include "raymath.h"

#include "components/text_button.h"
#include "core/scene_manager.h"
#include "core/scene_factory.h"

#include "space_invaders_config.h"

SpaceInvaders::SpaceInvaders() :
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

void SpaceInvaders::Init()
{
	Vector2 screenSize = config_.fieldDimension + config_.offset * 2;
	SetWindowSize((int)screenSize.x, (int)screenSize.y);
	SetTargetFPS(config_.targetFps);

	spaceshipTexture_ = LoadTexture("space_invaders/spaceship.png");
	spaceship_.SetUp(&config_, &spaceshipTexture_);
}

void SpaceInvaders::Update()
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

void SpaceInvaders::Draw()
{
	ClearBackground(config_.backgroundColor);

	std::string titleText = "Space Invaders";
	int titleTextWidth = MeasureText(titleText.c_str(), config_.fontSize);
	DrawText(titleText.c_str(), (GetScreenWidth() - titleTextWidth) / 2, (int)(config_.offset.y - config_.fontSize - config_.uiPadding), config_.fontSize, config_.secondaryHoverTextColor);

	Rectangle playfieldRect = {config_.offset.x, config_.offset.y, config_.fieldDimension.x, config_.fieldDimension.y};
	DrawRectangleRec(playfieldRect, config_.playfieldColor);
	DrawRectangleLinesEx({playfieldRect.x - config_.playfieldBorderThickness, playfieldRect.y - config_.playfieldBorderThickness, playfieldRect.width + config_.playfieldBorderThickness * 2, playfieldRect.height + config_.playfieldBorderThickness * 2}, config_.playfieldBorderThickness, config_.secondaryBackgroundColor);

	switch (state_)
	{
		case GameState::Menu:
			backButton_.Draw();
			startButton_.Draw();
			break;
		case GameState::Running:
			spaceship_.Draw();

			for (auto& laser : lasers_)
			{
				laser.Draw();
			}
			break;
		case GameState::GameOver:
			backButton_.Draw();
			startButton_.Draw();
			break;
	}
}

void SpaceInvaders::Shutdown()
{
	UnloadTexture(spaceshipTexture_);
}

void SpaceInvaders::StartGame()
{
	spaceship_.Init();

	state_ = GameState::Running;
}

void SpaceInvaders::UpdateGame()
{
	if (IsKeyDown(KEY_LEFT))
	{
		spaceship_.Move(true);
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		spaceship_.Move(false);
	}

	if (IsKeyDown(KEY_SPACE))
	{
		spaceship_.Fire(lasers_);
	}

	for (auto& laser : lasers_)
	{
		laser.Move();
	}

	CleanUpLasers();
}

void SpaceInvaders::CleanUpLasers()
{
	lasers_.erase(
		std::remove_if(lasers_.begin(), lasers_.end(),
					   [](const Laser& laser)
					   {
						   return !laser.IsActive();
					   }),
		lasers_.end()
	);
}