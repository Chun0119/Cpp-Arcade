#include "tetromino.h"

#include <array>

#include "raylib.h"
#include "raymath.h"

#include "tetris_config.h"
#include "tetromino_config.h"

Tetromino::Tetromino(const TetrisConfig* config, TetrominoType type) :
    config_(config),
    type_(type)
{ }

void Tetromino::Draw(Vector2 offset)
{
    auto cells = GetCells();

    for (const auto& cell : cells)
    {
        DrawRectangle(offset.x + cell.x * config_->tetrominoCellSize, offset.y + cell.y * config_->tetrominoCellSize, config_->tetrominoCellSize - config_->gridLineThickness, config_->tetrominoCellSize - config_->gridLineThickness, config_->tetrominosColor[static_cast<int>(type_)]);
    }
}

void Tetromino::Move(bool isLeft)
{
    int oldPosition = position_.x;
    position_.x += isLeft ? -1 : 1;

    if (IsValidPosition())
    {
        return;
    }

    position_.x = oldPosition;
}

void Tetromino::MoveDown()
{
    position_.y += 1;
}

void Tetromino::Rotate()
{
    int oldRotation = rotation_;

    rotation_ = (rotation_ + 1) % 4;

    if (IsValidPosition())
    {
        return;
    }

    // +1 wall kick
    int oldPosition = position_.x;
    position_.x += 1;

    if (IsValidPosition())
    {
        return;
    }

    // -1 wall kick
    position_.x = oldPosition - 1;

    if (IsValidPosition())
    {
        return;
    }

    // Restore
    position_.x = oldPosition;
    rotation_ = oldRotation;
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

bool Tetromino::IsValidPosition()
{
    auto cells = GetCells();

    for (const auto& cell : cells)
    {
        if (cell.x < 0 || cell.x >= config_->gridColumn)
        {
            return false;
        }
    }

    return true;
}
