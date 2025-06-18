#pragma once

#include "Board.h"

class Enemy {
public:
    int x, y, dx, dy;

    Enemy();

    void move(const std::array<std::array<int, WIDTH_SIZE>, HEIGHT_SIZE>& grid);
};