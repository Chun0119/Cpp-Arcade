#include "grid.h"

#include <vector>

#include "tetris_config.h"
#include "tetromino_config.h"

Grid::Grid(const TetrisConfig& config) :
    config_(config)
{ }

void Grid::Draw()
{
    for (int row = 0; row < config_.gridRow; ++row)
    {
        for (int column = 0; column < config_.gridColumn; ++column)
        {
            Color cellColor = IsCellEmpty(row, column) ? config_.playfieldColor : config_.tetrominosColor[cells_[row][column]];
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

bool Grid::IsCellEmpty(int row, int col) const
{
    return cells_[row][col] == -1;
}

bool Grid::IsRowFull(int row) const
{
    for (int column = 0; column < config_.gridColumn; ++column)
    {
        if (IsCellEmpty(row, column))
        {
            return false;
        }
    }

    return true;
}

void Grid::ClearLine(int clearedRow)
{
    for (int row = clearedRow; row > 0; --row)
    {
        cells_[row] = cells_[row - 1];
    }

    // Clear top row
    std::fill(cells_[0].begin(), cells_[0].end(), -1);
}

bool Grid::IsValidPosition(const Tetromino& tetromino) const
{
    auto cells = tetromino.GetCells();

    for (const auto& cell : cells)
    {
        if (cell.x < 0 || cell.x >= config_.gridColumn || cell.y < 0 || cell.y >= config_.gridRow)
        {
            return false;
        }

        if (!IsCellEmpty(cell.y,cell.x))
        {
            return false;
        }
    }

    return true;
}

void Grid::LockTetromino(const Tetromino& tetromino)
{
    auto cells = tetromino.GetCells();
    TetrominoType type = tetromino.GetType();

    for (const auto& cell : cells)
    {
        cells_[cell.y][cell.x] = static_cast<int>(type);
    }
}

int Grid::ClearLines()
{
    int completed = 0;

    for (int row = config_.gridRow - 1; row >= 0; --row)
    {
        if (IsRowFull(row))
        {
            ClearLine(row);
            completed++;
            row++;
        }
    }

    return completed;
}

