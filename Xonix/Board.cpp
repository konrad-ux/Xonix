#include "Board.h"

Board::Board()
{
    for (int i = 0; i < HEIGHT_SIZE; ++i)      //0 dla pustej przestrzeni, 1 dla scian
    {
        for (int j = 0; j < WIDTH_SIZE; ++j)
        {
            if (i == 0 || j == 0 || i == HEIGHT_SIZE - 1 || j == WIDTH_SIZE - 1) { grid[i][j] = 1; }
            else(grid[i][j] = 0);
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 10; j++) {
            grid[i][j] = 1;             // ustawianie wartosi 1 w tablicy dla percentage bar
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
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 10; j++) {
            grid[i][j] = 1;             // ustawianie wartosci 1 w tablicy dla percentage bar
        }
    }

}

void Board::drop(const int y, const int x)
{
    if (grid[y][x] == 0)
    {
        grid[y][x] = -1;        //wypelnianie planszy rekurencyjnie (-1 =zajeta przez enemies)
    }

    if (grid[y - 1][x] == 0)
    {
        drop(y - 1, x);
    }

    if (grid[y + 1][x] == 0)
    {
        drop(y + 1, x);
    }

    if (grid[y][x - 1] == 0)
    {
        drop(y, x - 1);
    }

    if (grid[y][x + 1] == 0)
    {
        drop(y, x + 1);
    }
}

void Board::finalize()          //zajmowanie zamalowanej przestrzeni
{
    for (int i = 0; i < HEIGHT_SIZE; ++i)
    {
        for (int j = 0; j < WIDTH_SIZE; ++j)
        {
            if (grid[i][j] == -1)      //zajete przez enemies komorki ->0
            {
                grid[i][j] = 0;
            }
            else if (grid[i][j] == 0)      //niezajete komorki ->1 (na zajete)
            {
                grid[i][j] = 1;
            }

            if (grid[i][j] == 2)       //slad ->1
            {
                grid[i][j] = 1;
            }
        }
    }
}
