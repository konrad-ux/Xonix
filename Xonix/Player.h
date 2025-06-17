#pragma once
#include "Board.h"

class Player
{
public:
    int     x, y, dx, dy;
    bool    alive, win;
    bool    isImmune; // Nowa flaga nietykalnoœci

public:
    Player();

public:
    void move(Board& board, float& timer, float delay);
    void handleInput();
};