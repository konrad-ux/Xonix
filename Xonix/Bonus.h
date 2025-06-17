#pragma once
#include "Board.h"
#include <SFML/Graphics/Rect.hpp>

class Player;
class Game;

class Bonus
{
public:
    int m_x, m_y;

public:
    Bonus(int x, int y);
    virtual ~Bonus() = default;

    int getX() const { return m_x; }
    int getY() const { return m_y; }

    virtual sf::FloatRect getBounds() const;

    virtual void applyEffect(Player& player, Game& game) = 0;
};