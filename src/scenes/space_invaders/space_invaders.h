#pragma once

#include "core/scene.h"

#include <vector>

#include "raylib.h"

#include "components/text_button.h"

#include "spaceship.h"
#include "laser.h"
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
	Texture2D spaceshipTexture_;

	std::vector<Laser> lasers_;

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

	void CleanUpLasers();
};