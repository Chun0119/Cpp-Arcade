#pragma once

#include <array>

#include "raylib.h"

#include "tetris_config.h"
#include "tetromino_config.h"

class Tetromino
{
private:
    const TetrisConfig* config_ = nullptr;

    TetrominoType type_ = TetrominoType::I;
    int rotation_ = 0;

    Cell position_ = {0, 0};

    bool IsValidPosition();

public:
    Tetromino() = default;
    Tetromino(const TetrisConfig* config, TetrominoType type);

    void Draw(Vector2 offset);

    void Move(bool isLeft);
    void MoveDown();
    void Rotate();

    std::array<Cell, 4> GetCells() const;
};