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

public:
    Tetromino() = default;
    Tetromino(const TetrisConfig* config, TetrominoType type);

    void Draw(Vector2 offset, bool isGhost);

    void Move(int dx, int dy);
    void Rotate();

    std::array<Cell, 4> GetCells() const;
    TetrominoType GetType() const;
    int GetRotation() const;
    void SetRotation(int rotation);
    Cell GetPosition() const;
    void SetPosition(Cell position);
};