#include "Base.h"

Base::Base() : Board()
{
    // Define the size of the safe area (for example, a 4x4 square in the center)
    const int baseWidth = 20;
    const int baseHeight = 20;
    const int startX = (WIDTH_SIZE - baseWidth) / 2;
    const int startY = (HEIGHT_SIZE - baseHeight) / 2;

    for (int i = 0; i < baseHeight; ++i) {
        for (int j = 0; j < baseWidth; ++j) {
            grid[startY + i][startX + j] = 1; // Mark as safe (like walls)
        }
    }
}
