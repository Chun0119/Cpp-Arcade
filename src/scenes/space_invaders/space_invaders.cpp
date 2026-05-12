#include "space_invaders.h"

#include <string>

#include "raylib.h"
#include "raymath.h"

#include "components/text_button.h"
#include "core/scene_manager.h"
#include "core/scene_factory.h"

#include "spaceship.h"
#include "laser.h"
#include "obstacle.h"
#include "alien.h"
#include "ufo.h"
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

	alien1Texture_ = LoadTexture("space_invaders/alien_1.png");
	alien2Texture_ = LoadTexture("space_invaders/alien_2.png");

	ufoTexture_ = LoadTexture("space_invaders/ufo.png");
	ufo_.SetUp(&config_, &ufoTexture_);
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

			for (auto& laser : spaceshipLasers_)
			{
				laser.Draw();
			}

			for (auto& obstacles : obstacles_)
			{
				obstacles.Draw();
			}

			for (auto& alien : aliens_)
			{
				alien.Draw();
			}

			for (auto& laser : alienLasers_)
			{
				laser.Draw();
			}

			ufo_.Draw();
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
	UnloadTexture(alien1Texture_);
	UnloadTexture(alien2Texture_);
	UnloadTexture(ufoTexture_);
}

void SpaceInvaders::StartGame()
{
	spaceship_.Init();
	spaceshipLasers_.clear();
	ResetObstacles();
	ResetAliens();
	ufoSpawnInterval_ = GetRandomValue(config_.ufoSpawnIntervalMin, config_.ufoSpawnIntervalMax);

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
		spaceship_.Fire(spaceshipLasers_);
	}

	for (auto& laser : spaceshipLasers_)
	{
		laser.Move();
	}
	CleanUpLasers(spaceshipLasers_);

	UpdateAliens();

	for (auto& laser : alienLasers_)
	{
		laser.Move();
	}
	CleanUpLasers(alienLasers_);

	UpdateUfo();
}

void SpaceInvaders::ResetAliens()
{
	aliens_.clear();

	float offsetY = config_.offset.y + config_.spaceshipSize;

	for (int row = 0; row < config_.alien1Row; ++row)
	{
		for (int column = 0; column < config_.alienColumn; ++column)
		{
			aliens_.emplace_back(&config_, &alien1Texture_, Vector2{config_.offset.x + column * config_.alienSize, offsetY + row * config_.alienSize});
		}
	}

	offsetY += (config_.alien2Row - 1) * config_.alienSize;

	for (int row = 0; row < config_.alien2Row; ++row)
	{
		for (int column = 0; column < config_.alienColumn; ++column)
		{
			aliens_.emplace_back(&config_, &alien2Texture_, Vector2{config_.offset.x + column * config_.alienSize, offsetY + row * config_.alienSize});
		}
	}
}

void SpaceInvaders::ResetObstacles()
{
	obstacles_.clear();

	int obstacleHeight = (int)config_.obstacleShape.size() * config_.obstacleBlockSize;
	int obstacleWidth = (int)config_.obstacleShape[0].size() * config_.obstacleBlockSize;
	float gap = (config_.fieldDimension.x - config_.obstacleAmount * obstacleWidth) / (config_.obstacleAmount + 1);
	float positionY = config_.offset.y + config_.fieldDimension.y - config_.spaceshipSize - obstacleHeight - config_.uiPadding * 2;

	for (int i = 0; i < config_.obstacleAmount; i++)
	{
		float offsetX = config_.offset.x + (i + 1) * gap + i * obstacleWidth;
		obstacles_.emplace_back(&config_, Vector2{offsetX, positionY});
	}
}

void SpaceInvaders::UpdateAliens()
{
	bool shouldMoveDown = false;

	for (const auto& alien : aliens_)
	{
		if (alien.IsOutOfField())
		{
			shouldMoveDown = true;
			break;
		}
	}

	if (shouldMoveDown)
	{
		isAlienMovingLeft_ = !isAlienMovingLeft_;
		MoveAliensDown();
	}

	for (auto& alien : aliens_)
	{
		alien.Move(isAlienMovingLeft_);
	}

	double currentTime = GetTime();
	if (currentTime - lastAlienFireTime_ < config_.alienFireInterval)
	{
		return;
	}

	lastAlienFireTime_ = currentTime;
	int randomIndex = GetRandomValue(0, aliens_.size() - 1);
	aliens_[randomIndex].Fire(alienLasers_);
}

void SpaceInvaders::MoveAliensDown()
{
	for (auto& alien : aliens_)
	{
		alien.MoveDown();
	}
}

void SpaceInvaders::UpdateUfo()
{
	ufo_.Move();

	double currentTime = GetTime();
	if (currentTime - lastUfoSpawnTime_ < ufoSpawnInterval_)
	{
		return;
	}

	lastUfoSpawnTime_ = currentTime;
	ufoSpawnInterval_ = GetRandomValue(config_.ufoSpawnIntervalMin, config_.ufoSpawnIntervalMax);

	ufo_.Spawn();
}

void SpaceInvaders::CleanUpLasers(std::vector<Laser>& lasers)
{
	lasers.erase(
		std::remove_if(lasers.begin(), lasers.end(),
					   [](const Laser& laser)
					   {
						   return !laser.IsActive();
					   }),
		lasers.end()
	);
}