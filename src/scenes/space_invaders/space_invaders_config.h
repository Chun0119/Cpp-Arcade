#pragma once

#include <vector>
#include <string>

#include "raylib.h"

struct SpaceInvadersConfig
{
	int targetFps = 60;
	std::string highScoreFileName = "space_invaders_highscore.txt";

	// PLAYFIELD
	Color backgroundColor = {11, 19, 32, 255};   // #0B1320
	Vector2 fieldDimension = {900.0f, 750.0f};
	Vector2 offset = {16.0f, 66.0f};
	Color playfieldColor = {17, 27, 46, 255};   // #111B2E
	float playfieldBorderThickness = 5.0f;

	// SPACESHIP
	float spaceshipSpeed = 4.0f;
	float spaceshipSize = 60.0f;
	double spaceshipFireInterval = 0.35;
	int spaceshipLives = 5;
	float spaceshipLivesSize = 40.0f;

	// LASER
	float laserSpeed = 4.0f;
	Vector2 laserSize = {4, 15};
	Color laserColor = {180, 255, 80, 255};    // #B4FF50

	// OBSTACLE
	int obstacleAmount = 4;
	int obstacleBlockSize = 4;   // #5A82AA
	Color obstacleColor = {90, 130, 170, 255};   // #5A82AA
	std::vector<std::vector<int>> obstacleShape = {
		{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
		{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}
	};

	// ALIEN
	Vector2 alienSpeed = {2.0f, 8.0f};
	float alienSize = 50.0f;
	int alien1Row = 2;
	int alien2Row = 3;
	int alienColumn = 8;
	double alienFireInterval = 0.35;
	int alien1Score = 10;
	int alien2Score = 20;

	// UFO
	float ufoSpeed = 2.5f;
	float ufoSize = 60.0f;
	int ufoSpawnIntervalMin = 10;
	int ufoSpawnIntervalMax = 20;
	int ufoScore = 100;

	// UI LAYOUT
	Color playerScoreColor = {220, 240, 255, 255}; // #DCF0FF

	float buttonWidth = 200.0f;
	float buttonHeight = 50.0f;

	int uiPadding = 16;
	int fontSize = 20;

	Color primaryBackgroundColor = {255, 209, 102, 255};   // #FFD166
	Color primaryTextColor = {11, 19, 32, 255};    // dark text
	Color primaryHoverBackgroundColor = {255, 220, 130, 255}; // slightly brighter
	Color primaryHoverTextColor = {11, 19, 32, 255};

	Color secondaryBackgroundColor = {28, 42, 70, 255};
	Color secondaryTextColor = {230, 237, 243, 255}; // soft white text
	Color secondaryHoverBackgroundColor = {40, 60, 95, 255};  // brighter blue-ish
	Color secondaryHoverTextColor = {255, 255, 255, 255};
};