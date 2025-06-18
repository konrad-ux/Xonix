#include "Board.h"

Board::Board()
{
    for (int i = 0; i < HEIGHT_SIZE; ++i)
    {
        for (int j = 0; j < WIDTH_SIZE; ++j)
        {
            if (i == 0 || j == 0 || i == HEIGHT_SIZE - 1 || j == WIDTH_SIZE - 1)
            {
                grid[i][j] = 1;
            }
            else
            {
                grid[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            grid[i][j] = 1;
        }
    }
}

void Board::reset()
{
    for (int i = 1; i < HEIGHT_SIZE - 1; ++i)
    {
        for (int j = 1; j < WIDTH_SIZE - 1; ++j)
        {
            grid[i][j] = 0;
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            grid[i][j] = 1;
        }
    }
}

void Board::drop(int y, int x)
{
    if (y < 0 || y >= HEIGHT_SIZE || x < 0 || x >= WIDTH_SIZE)
    {
        return;
    }

    if (grid[y][x] == 0)
    {
        grid[y][x] = -1;

        if (y - 1 > 0)
        {
            drop(y - 1, x);
        }
        if (y + 1 < HEIGHT_SIZE - 1)
        {
            drop(y + 1, x);
        }
        if (x - 1 > 0)
        {
            drop(y, x - 1);
        }
        if (x + 1 < WIDTH_SIZE - 1)
        {
            drop(y, x + 1);
        }
    }
}

void Board::finalize()
{
    for (int i = 0; i < HEIGHT_SIZE; ++i)
    {
        for (int j = 0; j < WIDTH_SIZE; ++j)
        {
            if (grid[i][j] == -1)
            {
                grid[i][j] = 0;
            }
            else if (grid[i][j] == 0 || grid[i][j] == 2)
            {
                grid[i][j] = 1;
            }
        }
    }
}