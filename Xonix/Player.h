#pragma once

#include "Board.hpp"

class Player
{
public:
    int     x, y, dx, dy;
    bool    alive, win;

public:
    Player();

public:
    void move(Board& board, float& timer, float delay);
    void handleInput();
};

