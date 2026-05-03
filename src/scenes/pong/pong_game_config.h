#pragma once

struct PongGameConfig
{
	int targetFps = 60;

	int winningScore = 10;

	// PLAYFIELD
	Color backgroundColor = {11, 19, 32, 255};   // #0B1320
	Vector2 fieldDimension = {1200.0f, 600.0f};
	Vector2 offset = {16.0f, 66.0f};
	Color playfieldColor = {17, 27, 46, 255};   // #111B2E
	Color fieldLineColor = {62, 235, 127, 80};  // transparent green
	float playfieldBorderThickness = 5.0f;

	// BALL
	int ballStartAngleRange = 45;
	float ballSpeed = 7.0f;
	float ballRadius = 20.0f;
	Color ballColor = {102, 255, 170, 255};

	// PADDLE
	Vector2 paddleSize = {25.0f, 125.0f};
	float paddleSpeed = 4.0f;
	float paddleMoveThreshold = 10.0f;
	Color playerPaddleColor = {62, 235, 127, 255};
	Color aiPaddleColor = {255, 77, 77, 255};

	// UI LAYOUT
	Color playerScoreColor = {102, 255, 170, 255};
	Color aiScoreColor = {255, 77, 77, 255};

	Color winColor = {62, 235, 127, 255}; // green
	Color loseColor = {255, 77, 77, 255};  // red

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