#include "Enemy.h"
#include <cstdlib>

Enemy::Enemy()
{
    // Losuje pozycjê startow¹ wewn¹trz planszy do gry.
    // Odejmujemy 2, aby nie pojawiaæ siê na œcianach (które s¹ na indeksach 0 i WIDTH_SIZE-1).
    int tileX, tileY;

    // Pêtla do-while zapewnia, ¿e wróg nie pojawi siê w obszarze tablicy wyników
    // (który jest zablokowany jako œciana).
    do
    {
        tileX = 1 + rand() % (WIDTH_SIZE - 2);
        tileY = 1 + rand() % (HEIGHT_SIZE - 2);
    } while (tileY < 4 && tileX < 10); // Sprawdza, czy pozycja nie jest w lewym górnym rogu (obszar wyniku)

    // Przelicz pozycjê z kafelków na piksele
    x = tileX * TILE_SIZE;
    y = tileY * TILE_SIZE;

    // Losuje wektor ruchu (prêdkoœæ)
    do
    {
        dx = 4 - rand() % 9;
        dy = 4 - rand() % 9;
    } while (dx == 0 || dy == 0); // Pêtla zapewnia, ¿e wróg nie bêdzie sta³ w miejscu
}

void Enemy::move(std::array<std::array<int, WIDTH_SIZE>, HEIGHT_SIZE> grid)
{
    x += dx;
    // Sprawdzenie kolizji ze œcian¹ (kafelek o wartoœci 1)
    if (grid[y / TILE_SIZE][x / TILE_SIZE] == 1)
    {
        dx = -dx;
        x += dx;
    }

    y += dy;
    // Sprawdzenie kolizji ze œcian¹
    if (grid[y / TILE_SIZE][x / TILE_SIZE] == 1)
    {
        dy = -dy;
        y += dy;
    }
}