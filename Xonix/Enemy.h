#pragma once
#include "Board.h"

class Enemy
{
public:
    int x, y, dx, dy;

public:
    Enemy();

public:
    void move(std::array< std::array< int, WIDTH_SIZE >, HEIGHT_SIZE > grid);     //tab okreslonych elem o stal rozmiarze
};
