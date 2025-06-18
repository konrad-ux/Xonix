#pragma once

#include <array>

constexpr int HEIGHT_SIZE = 40;
constexpr int WIDTH_SIZE = 40;
constexpr int TILE_SIZE = 18;

class Board {
public:
    std::array<std::array<int, WIDTH_SIZE>, HEIGHT_SIZE> grid{};

    Board();

    void reset();
    void drop(int y, int x);
    void finalize();
};