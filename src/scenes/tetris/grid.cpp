#include "grid.h"

#include <vector>

#include "tetris_config.h"

Grid::Grid(const TetrisConfig& config) :
    config_(config)
{ }

void Grid::Draw()
{
    for (int row = 0; row < config_.gridRow; ++row)
    {
        for (int column = 0; column < config_.gridColumn; ++column)
        {
            int tetrominoType = cells_[row][column];
            Color cellColor = tetrominoType == -1 ? config_.playfieldColor : config_.tetrominosColor[tetrominoType];
            DrawRectangle(config_.offset.x + column * config_.tetrominoCellSize, config_.offset.y + row * config_.tetrominoCellSize, config_.tetrominoCellSize - config_.gridLineThickness, config_.tetrominoCellSize - config_.gridLineThickness, cellColor);
        }
    }
}

void Grid::Init()
{
    cells_.clear();

    cells_.resize(config_.gridRow, std::vector<int>(config_.gridColumn, 0));

    for (int row = 0; row < config_.gridRow; ++row)
    {
        for (int column = 0; column < config_.gridColumn; ++column)
        {
            cells_[row][column] = -1;
        }
    }
}
