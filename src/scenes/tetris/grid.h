#pragma once

#include <vector>

#include "tetromino.h"
#include "tetris_config.h"

class Grid
{
private:
    const TetrisConfig& config_;

    std::vector<std::vector<int>> cells_;

    bool IsCellEmpty(int row, int col) const;
    bool IsRowFull(int row) const;
    void ClearLine(int clearedRow);

public:
    Grid() = default;
    Grid(const TetrisConfig& config);

    void Draw();

    void Init();
    bool IsValidPosition(const Tetromino& tetromino) const;
    void LockTetromino(const Tetromino& tetromino);
    int ClearLines();
};