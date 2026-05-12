#pragma once

#include "core/scene.h"

#include <vector>

#include "raylib.h"

#include "components/text_button.h"

#include "spaceship.h"
#include "laser.h"
#include "obstacle.h"
#include "alien.h"
#include "ufo.h"
#include "space_invaders_config.h"

class SpaceInvaders : public Scene
{
private:
	SpaceInvadersConfig config_;

	enum class GameState
	{
		Menu,
		Running,
		GameOver
	};

	GameState state_ = GameState::Menu;

	Spaceship spaceship_;
	Texture2D spaceshipTexture_ = {};
	std::vector<Laser> spaceshipLasers_;

	std::vector<Obstacle> obstacles_;

	std::vector<Alien> aliens_;
	Texture2D alien1Texture_ = {};
	Texture2D alien2Texture_ = {};
	bool isAlienMovingLeft_ = false;
	std::vector<Laser> alienLasers_;
	double lastAlienFireTime_ = 0;

	Ufo ufo_;
	Texture2D ufoTexture_ = {};
	double lastUfoSpawnTime_ = 0;
	double ufoSpawnInterval_ = 0;

	TextButton backButton_;
	TextButton startButton_;

public:
	SpaceInvaders();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Shutdown() override;

	void StartGame();
	void UpdateGame();

	void ResetObstacles();
	void ResetAliens();

	void UpdateAliens();
	void MoveAliensDown();

	void UpdateUfo();

	void CleanUpLasers(std::vector<Laser>& lasers);
};