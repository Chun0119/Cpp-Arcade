#pragma once

struct PongGameConfig
{
	int targetFps = 60;

	int winningScore = 10;

	// PLAYFIELD
	Color backgroundColor = {11, 19, 32, 255};   // #0B1320
	Vector2 fieldDimension = {1200.0f, 800.0f};
	Color fieldLineColor = {255, 77, 77, 255};   // #FF4D4D

	// BALL
	Vector2 ballStartDirection = {4.0f, 4.0f};
	float ballRadius = 20.0f;
	Color ballColor = {255, 77, 77, 255};   // #FF4D4D

	// PADDLE
	Vector2 paddleSize = {25.0f, 125.0f};
	float paddleSpeed = 6.0f;
	Color paddleColor = {255, 77, 77, 255};   // #FF4D4D

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