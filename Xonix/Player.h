#pragma once

#include "Board.h"
#include <SFML/Graphics/Rect.hpp>

class Player {
public:
    Player();

    void move(Board& board, float& timer, float delay);
    void handleInput();

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getDx() const { return m_dx; }
    int getDy() const { return m_dy; }

    void setPosition(int x, int y);
    void resetDirection();

    bool isAlive() const { return m_alive; }
    void setAlive(bool isAlive) { m_alive = isAlive; }

    bool hasWon() const { return m_win; }
    void setWin(bool hasWon) { m_win = hasWon; }

    bool isImmune() const { return m_isImmune; }
    void setImmunity(bool immune) { m_isImmune = immune; }

    sf::FloatRect getBounds() const;

private:
    int m_x, m_y, m_dx, m_dy;
    bool m_alive;
    bool m_win;
    bool m_isImmune;
};