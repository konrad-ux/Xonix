#include "Player.h"
#include <SFML/Window/Keyboard.hpp>

Player::Player() : x(9), y(3), dx(0), dy(0), alive(true), win(false)
{
    //puste cialo
}

void Player::move(Board& board, float& timer, const float delay)
{
    if (timer > delay)
    {
        x += dx;
        y += dy;

        if (x < 0)
        {
            x = 0;
        }

        if (x >= WIDTH_SIZE)
        {
            x = WIDTH_SIZE - 1;
        }

        if (y < 0)
        {
            y = 0;
        }

        if (y >= HEIGHT_SIZE)
        {
            y = HEIGHT_SIZE - 1;
        }

        if (board.grid[y][x] == 2)     //kolizja z wlasnym sladem
        {
            alive = false;
        }

        if (board.grid[y][x] == 0)     //tworzenie sladu
        {
            board.grid[y][x] = 2;
        }

        timer = 0;
    }
}

void Player::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        dx = -1; dy = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        dx = 1; dy = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        dx = 0; dy = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        dx = 0; dy = 1;
    }
}

