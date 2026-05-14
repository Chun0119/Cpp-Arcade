#pragma once

#include "raylib.h"

struct TetrisConfig
{
	int targetFps = 60;
	std::string highScoreFileName = "tetris_highscore.txt";

	// PLAYFIELD
	Color backgroundColor = {11, 19, 32, 255};   // #0B1320
	Vector2 fieldDimension = {900.0f, 750.0f};
	Vector2 offset = {16.0f, 66.0f};
	Color playfieldColor = {17, 27, 46, 255};   // #111B2E
	float playfieldBorderThickness = 5.0f;
	Color panelColor = {28, 43, 72, 255}; // #1C2B48

	// GRID
	Color gridLineColor = {40, 65, 110, 120}; // translucent blue

	// BLOCKS
	Color iBlockColor = {0, 240, 255, 255}; // #00F0FF
	Color oBlockColor = {255, 230, 70, 255}; // #FFE646
	Color tBlockColor = {180, 70, 255, 255}; // #B446FF
	Color sBlockColor = {62, 235, 127, 255}; // #3EEB7F
	Color zBlockColor = {255, 77, 77, 255}; // #FF4D4D
	Color jBlockColor = {70, 120, 255, 255}; // #4678FF
	Color lBlockColor = {255, 150, 40, 255}; // #FF9628

	// UI LAYOUT
	Color borderColor = {50, 80, 140, 255}; // #32508C
	Color uiLabelColor = {180, 210, 255, 255}; // #B4D2FF
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