#include "Player.h"
#include "Board.h"
#include <SFML/Window/Keyboard.hpp>

Player::Player() :
    m_x(9),
    m_y(3),
    m_dx(0),
    m_dy(0),
    m_alive(true),
    m_win(false),
    m_isImmune(false) {
}

void Player::move(Board& board, float& timer, float delay)
{
    if (timer > delay)
    {
        m_x += m_dx;
        m_y += m_dy;

        if (m_x < 0) m_x = 0;
        if (m_x >= WIDTH_SIZE) m_x = WIDTH_SIZE - 1;
        if (m_y < 0) m_y = 0;
        if (m_y >= HEIGHT_SIZE) m_y = HEIGHT_SIZE - 1;

        if (board.grid[m_y][m_x] == 2 && !m_isImmune)
        {
            m_alive = false;
        }

        if (board.grid[m_y][m_x] == 0)
        {
            board.grid[m_y][m_x] = 2;
        }

        timer = 0;
    }
}

void Player::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_dx = -1;
        m_dy = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_dx = 1;
        m_dy = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_dx = 0;
        m_dy = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_dx = 0;
        m_dy = 1;
    }
}

void Player::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

void Player::resetDirection()
{
    m_dx = 0;
    m_dy = 0;
}

sf::FloatRect Player::getBounds() const
{
    return sf::FloatRect(
        static_cast<float>(m_x * TILE_SIZE),
        static_cast<float>(m_y * TILE_SIZE),
        static_cast<float>(TILE_SIZE),
        static_cast<float>(TILE_SIZE)
    );
}