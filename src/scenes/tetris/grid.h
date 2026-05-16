#pragma once

#include <vector>

#include "tetris_config.h"

class Grid
{
private:
    const TetrisConfig& config_;

    std::vector<std::vector<int>> cells_;

public:
    Grid() = default;
    Grid(const TetrisConfig& config);

    void Draw();

    void Init();
};