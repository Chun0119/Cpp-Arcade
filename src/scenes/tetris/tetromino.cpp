#include "tetromino.h"

#include <array>

#include "raylib.h"
#include "raymath.h"

#include "tetris_config.h"
#include "tetromino_config.h"

Tetromino::Tetromino(const TetrisConfig* config, TetrominoType type) :
    config_(config),
    type_(type)
{
    position_.x = (config_->gridColumn - 4) / 2;
    position_.y = 0;
}

void Tetromino::Draw(Vector2 offset, bool isGhost)
{
    auto cells = GetCells();

    Color color = config_->tetrominosColor[static_cast<int>(type_)];
    if (isGhost)
    {
        color.a *= 0.5f;
    }

    for (const auto& cell : cells)
    {
        DrawRectangle(offset.x + cell.x * config_->tetrominoCellSize, offset.y + cell.y * config_->tetrominoCellSize, config_->tetrominoCellSize - config_->gridLineThickness, config_->tetrominoCellSize - config_->gridLineThickness, color);
    }
}

void Tetromino::Move(int dx, int dy)
{
    position_.x += dx;
    position_.y += dy;
}

void Tetromino::Rotate()
{
    rotation_ = (rotation_ + 1) % 4;
}

std::array<Cell, 4> Tetromino::GetCells() const
{
    std::array<Cell, 4> result;

    const auto& cells = kTetrominos[static_cast<int>(type_)].rotations[rotation_];

    for (int i = 0; i < 4; i++)
    {
        result[i] = {position_.x + cells[i].x, position_.y + cells[i].y};
    }

    return result;
}

TetrominoType Tetromino::GetType() const
{
    return type_;
}

int Tetromino::GetRotation() const
{
    return rotation_;
}

void Tetromino::SetRotation(int rotation)
{
    rotation_ = rotation;
}

Cell Tetromino::GetPosition() const
{
    return position_;
}

void Tetromino::SetPosition(Cell position)
{
    position_ = position;
}