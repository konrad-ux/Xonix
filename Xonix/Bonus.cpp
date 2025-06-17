#include "Bonus.h"

Bonus::Bonus(int x, int y) : m_x(x), m_y(y) {}

sf::FloatRect Bonus::getBounds() const
{
    return sf::FloatRect(
        static_cast<float>(m_x * TILE_SIZE),
        static_cast<float>(m_y * TILE_SIZE),
        static_cast<float>(TILE_SIZE),
        static_cast<float>(TILE_SIZE)
    );
}