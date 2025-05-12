#pragma once

#include <array>

constexpr int HEIGHT_SIZE = 25;     //zmienne stale podczas kompilacji(rozmiary okna i kafelka)
constexpr int WIDTH_SIZE = 40;
constexpr int TILE_SIZE = 18;

class Board
{
public:
    std::array< std::array< int, WIDTH_SIZE >, HEIGHT_SIZE > grid{}; //tablica grid o znanym rozmiarze

public:
    Board();

public:
    void reset();
    void drop(int y, int x);
    void finalize();
};
