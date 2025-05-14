#include "Enemy.h"
#include <cstdlib>

Enemy::Enemy()
{
    x = y = 300;
    dx = 4 - rand() % 9;
    dy = 4 - rand() % 9;
    if (dx == 0 || dy == 0) { dx = 1, dy = 1; }
}

void Enemy::move(std::array< std::array< int, WIDTH_SIZE >, HEIGHT_SIZE > grid)
{
    x += dx;
    if (grid[y / 18][x / 18] == 1)     //odbicia
    {
        dx = -dx;
        x += dx;
    }

    y += dy;
    if (grid[y / 18][x / 18] == 1)
    {
        dy = -dy;
        y += dy;
    }
}
