#pragma once

#include "raylib.h"

struct SnakeGameConfig
{
	// GRID / WORLD
	float cellSize = 20.0f;
	Vector2 cellDimension = {20.0f, 20.0f};

	// Game area offset (where grid starts on screen)
	Vector2 offset = {100.0f, 100.0f};

	int targetFps = 60;
	float moveDelaySeconds = 0.2f; // snake speed

	// PLAYFIELD
	Color backgroundColor = {11, 19, 32, 255};   // #0B1320
	Color playfieldColor = {17, 27, 46, 255};   // #111B2E
	float playfieldBorderThickness = 5.0f;

	// SNAKE
	float snakeRoundness = 0.25f;
	Color snakeBodyColor = {62, 235, 127, 255}; // #3EEB7F
	Color snakeHeadColor = {102, 255, 170, 255}; // #66FFAA
	Vector2 snakeStartPosition = {5, 5};
	int snakeStartLength = 3;
	Vector2 snakeStartDirection = {1, 0};

	// FOOD
	float foodRadiusScale = 0.35f;
	float foodGlowRadiusMultiplier = 1.6f;
	Color foodColor = {255, 77, 77, 255};   // #FF4D4D
	Color foodGlowColor = {255, 77, 77, 80};    // transparent glow

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