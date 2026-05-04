#pragma once

#include "raylib.h"

class GridLayout
{
private:
    Vector2 start_;
    Vector2 cellSize_;
    float spacing_;
    int columns_;

public:
    GridLayout(Vector2 start, Vector2 cellSize, float spacing, int columns);

    Rectangle GetCell(int index) const;
};