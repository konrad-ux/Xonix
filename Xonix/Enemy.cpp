#include "Enemy.h"
#include <cstdlib>

Enemy::Enemy()
{
    int tileX, tileY;

    do
    {
        tileX = 1 + rand() % (WIDTH_SIZE - 2);
        tileY = 1 + rand() % (HEIGHT_SIZE - 2);
    } while (tileY < 4 && tileX < 10);

    x = tileX * TILE_SIZE;
    y = tileY * TILE_SIZE;

    do
    {
        dx = 4 - rand() % 9;
        dy = 4 - rand() % 9;
    } while (dx == 0 || dy == 0);
}

void Enemy::move(const std::array<std::array<int, WIDTH_SIZE>, HEIGHT_SIZE>& grid)
{
    x += dx;
    if (grid[y / TILE_SIZE][x / TILE_SIZE] == 1)
    {
        dx = -dx;
        x += dx;
    }

    y += dy;
    if (grid[y / TILE_SIZE][x / TILE_SIZE] == 1)
    {
        dy = -dy;
        y += dy;
    }
}