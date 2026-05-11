#pragma once

struct SpaceInvadersConfig
{
	int targetFps = 60;

	// PLAYFIELD
	Color backgroundColor = {11, 19, 32, 255};   // #0B1320
	Vector2 fieldDimension = {900.0f, 700.0f};
	Vector2 offset = {16.0f, 66.0f};
	Color playfieldColor = {17, 27, 46, 255};   // #111B2E
	float playfieldBorderThickness = 5.0f;

	// SPACESHIP
	float spaceshipSpeed = 4.0f;
	float spaceshipSize = 80.0f;
	double spaceshipFireInterval = 0.35;

	// LASER
	float laserSpeed = 4.0f;
	Vector2 laserSize = {4, 15};
	Color laserColor = {62, 235, 127, 80};

	// UI LAYOUT
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