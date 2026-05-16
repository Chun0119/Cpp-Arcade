#pragma once

#include <array>
#include <string>

#include "raylib.h"

struct TetrisConfig
{
	int targetFps = 60;
	std::string highScoreFileName = "tetris_highscore.txt";

	// PLAYFIELD
	Color backgroundColor = {11, 19, 32, 255};   // #0B1320
	Vector2 offset = {16.0f, 66.0f};
	Color playfieldColor = {17, 27, 46, 255};   // #111B2E
	float playfieldBorderThickness = 5.0f;

	// SIDE PANEL
	int panelWidth = 300;
	Color panelColor = {28, 43, 72, 255}; // #1C2B48

	// GRID
	int gridRow = 20;
	int gridColumn = 10;
	int gridLineThickness = 1;
	Color gridLineColor = {40, 65, 110, 120}; // translucent blue

	// BLOCKS
	std::array<Color, 7> tetrominosColor =
	{
		Color{0, 240, 255, 255}, // #00F0FF		I
		Color{255, 230, 70, 255}, // #FFE646	O
		Color{180, 70, 255, 255}, // #B446FF	T
		Color{62, 235, 127, 255}, // #3EEB7F	S
		Color{255, 77, 77, 255}, // #FF4D4D		Z
		Color{70, 120, 255, 255}, // #4678FF	J
		Color{255, 150, 40, 255} // #FF9628		L
	};
	int tetrominoCellSize = 32;
	float tetrominoMoveInterval = 0.2f;
	float tetrominoDefaultDropDelay = 0.5f;
	float tetrominoFastDropDelay = 0.1f;

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