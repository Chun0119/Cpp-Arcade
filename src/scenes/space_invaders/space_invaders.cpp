#include "space_invaders.h"

#include <string>
#include <fstream>

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

	LoadHighScore();

	backgroundMusic_ = LoadMusicStream("space_invaders/bgm.ogg");
	PlayMusicStream(backgroundMusic_);

	shootSound_ = LoadSound("space_invaders/laser.ogg");
	explosionSound_ = LoadSound("space_invaders/explosion.ogg");
	bonusSound_ = LoadSound("space_invaders/bonus.ogg");
}

void SpaceInvaders::Update()
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

void SpaceInvaders::Draw()
{
	ClearBackground(config_.backgroundColor);

	std::string titleText = "Space Invaders";
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
		{
			spaceship_.Draw();

			for (auto& obstacles : obstacles_)
			{
				obstacles.Draw();
			}

			for (auto& alien : aliens_)
			{
				alien.Draw();
			}

			ufo_.Draw();

			for (auto& laser : spaceshipLasers_)
			{
				laser.Draw();
			}

			for (auto& laser : alienLasers_)
			{
				laser.Draw();
			}

			Rectangle source = {0.0f, 0.0f, (float)spaceshipTexture_.width, (float)spaceshipTexture_.height};
			Vector2 origin = {0.0f, 0.0f};
			for (int i = 0; i < lives_; i++)
			{
				Rectangle dest = {config_.offset.x + i * config_.spaceshipSize, config_.offset.y + config_.fieldDimension.y + config_.uiPadding, config_.spaceshipLivesSize, config_.spaceshipLivesSize};
				DrawTexturePro(spaceshipTexture_, source, dest, origin, 0.0f, WHITE);
			}
			break;
		}
		case GameState::GameOver:
			std::string endingMessage = lives_ <= 0 ? "Game Over" : "Congratulation!";
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

void SpaceInvaders::Shutdown()
{
	UnloadTexture(spaceshipTexture_);
	UnloadTexture(alien1Texture_);
	UnloadTexture(alien2Texture_);
	UnloadTexture(ufoTexture_);
	UnloadMusicStream(backgroundMusic_);
	UnloadSound(shootSound_);
	UnloadSound(explosionSound_);
	UnloadSound(bonusSound_);
}

void SpaceInvaders::StartGame()
{
	spaceship_.Init();
	spaceshipLasers_.clear();
	ResetObstacles();
	ResetAliens();
	ufoSpawnInterval_ = GetRandomValue(config_.ufoSpawnIntervalMin, config_.ufoSpawnIntervalMax);

	lives_ = config_.spaceshipLives;
	score_ = 0;

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
		if (spaceship_.Fire(spaceshipLasers_))
		{
			PlaySound(shootSound_);
		}
	}

	for (auto& laser : spaceshipLasers_)
	{
		laser.Move();
	}

	UpdateAliens();

	for (auto& laser : alienLasers_)
	{
		laser.Move();
	}

	UpdateUfo();

	CheckForCollisions();
	CleanUp();

	if (lives_ <= 0 || aliens_.empty())
	{
		if (score_ > highScore_)
		{
			highScore_ = score_;
			SaveHighScore();
		}
		state_ = GameState::GameOver;
	}
}

void SpaceInvaders::ResetAliens()
{
	aliens_.clear();

	float offsetY = config_.offset.y + config_.spaceshipSize;

	for (int row = 0; row < config_.alien1Row; ++row)
	{
		for (int column = 0; column < config_.alienColumn; ++column)
		{
			aliens_.emplace_back(&config_, &alien1Texture_, Vector2{config_.offset.x + column * config_.alienSize, offsetY + row * config_.alienSize}, 1);
		}
	}

	offsetY += (config_.alien2Row - 1) * config_.alienSize;

	for (int row = 0; row < config_.alien2Row; ++row)
	{
		for (int column = 0; column < config_.alienColumn; ++column)
		{
			aliens_.emplace_back(&config_, &alien2Texture_, Vector2{config_.offset.x + column * config_.alienSize, offsetY + row * config_.alienSize}, 0);
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
	if (aliens_.empty())
	{
		return;
	}

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
	int randomIndex = GetRandomValue(0, (int)aliens_.size() - 1);
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

void SpaceInvaders::CheckForCollisions()
{
	for (auto& laser : spaceshipLasers_)
	{
		if (!laser.IsActive())
		{
			continue;
		}

		// Spaceship laser VS ufo
		if (CheckCollisionRecs(laser.GetRect(), ufo_.GetRect()))
		{
			laser.OnHit();
			ufo_.OnHit();
			score_ += config_.ufoScore;
			PlaySound(bonusSound_);
			continue;
		}

		// Spaceship laser VS alien
		for (auto& alien : aliens_)
		{
			if (!alien.IsActive())
			{
				continue;
			}

			if (CheckCollisionRecs(laser.GetRect(), alien.GetRect()))
			{
				laser.OnHit();
				alien.OnHit();
				score_ += alien.GetScore();
				PlaySound(explosionSound_);
			}
		}

		if (!laser.IsActive())
		{
			continue;
		}

		// Spaceship laser VS obstacle
		for (auto& obstacle : obstacles_)
		{
			for (auto& block : obstacle.GetBlocks())
			{
				if (!block.IsActive())
				{
					continue;
				}

				if (CheckCollisionRecs(laser.GetRect(), block.GetRect()))
				{
					laser.OnHit();
					block.OnHit();
				}
			}
		}
	}

	for (auto& laser : alienLasers_)
	{
		if (!laser.IsActive())
		{
			continue;
		}

		// Alien laser VS spaceship
		if (CheckCollisionRecs(laser.GetRect(), spaceship_.GetRect()))
		{
			laser.OnHit();
			lives_--;
			PlaySound(explosionSound_);
			continue;
		}

		// Alien laser VS obstacle
		for (auto& obstacle : obstacles_)
		{
			for (auto& block : obstacle.GetBlocks())
			{
				if (!block.IsActive())
				{
					continue;
				}

				if (CheckCollisionRecs(laser.GetRect(), block.GetRect()))
				{
					laser.OnHit();
					block.OnHit();
				}
			}
		}
	}

	for (auto& alien : aliens_)
	{
		if (!alien.IsActive())
		{
			continue;
		}

		// Alien VS spaceship
		if (CheckCollisionRecs(alien.GetRect(), spaceship_.GetRect()))
		{
			alien.OnHit();
			lives_--;
			PlaySound(explosionSound_);
			continue;
		}

		// Alien VS obstacle
		for (auto& obstacle : obstacles_)
		{
			for (auto& block : obstacle.GetBlocks())
			{
				if (!block.IsActive())
				{
					continue;
				}

				if (CheckCollisionRecs(alien.GetRect(), block.GetRect()))
				{
					block.OnHit();
				}
			}
		}
	}
}

void SpaceInvaders::CleanUp()
{
	CleanUpInactiveObjects(spaceshipLasers_);
	CleanUpInactiveObjects(aliens_);
	CleanUpInactiveObjects(alienLasers_);
	for (auto& obstacle : obstacles_)
	{
		CleanUpInactiveObjects(obstacle.GetBlocks());
	}
}

template<typename T>
void SpaceInvaders::CleanUpInactiveObjects(std::vector<T>& objects)
{
	objects.erase(
		std::remove_if(objects.begin(), objects.end(),
					   [](const T& object)
					   {
						   return !object.IsActive();
					   }),
		objects.end()
	);
}

void SpaceInvaders::LoadHighScore()
{
	highScore_ = 0;
	std::ifstream highScoreFile(config_.highScoreFileName);
	if (highScoreFile.is_open())
	{
		highScoreFile >> highScore_;
		highScoreFile.close();
	}
}

void SpaceInvaders::SaveHighScore()
{
	std::ofstream highScoreFile(config_.highScoreFileName);
	if (highScoreFile.is_open())
	{
		highScoreFile << highScore_;
		highScoreFile.close();
	}
}