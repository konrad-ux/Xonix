#pragma once

#include "Board.h"
#include "Enemy.h"
#include "Player.h"
#include "Bonus.h"
#include "Teleport.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include<windows.h>
#include<iostream>
#include <vector>

class Game
{
public:
    Game();
public:
    void run();


private:
    void handleEvents();
    void draw();
    void checkPlayerBonusCollision(Player& player);
    void checkPlayerTeleportCollision(Player& player, Teleport& m_teleport1, Teleport& m_teleport2);
    float calculateOccupiedPercentage();

private:
    Board                   m_board;
    Player                  m_player;
    Teleport                m_teleport1;
    Teleport                m_teleport2;
    std::vector< Enemy >    m_enemies;
    std::vector<Bonus>      m_bonuses;

    sf::Texture             m_t1, m_t2, m_t3, m_t4, m_t5, m_t6;
    sf::Sprite              m_tile, m_gameOver, m_enemy, m_bonus, m_win, s_teleport1, s_teleport2;
    sf::Font                m_font;
    sf::Text                percentageText;
    sf::SoundBuffer         m_teleportSoundBuffer;
    sf::Sound               m_teleportSound;
    sf::SoundBuffer         m_gameoverSoundBuffer;
    sf::Sound               m_gameoverSound;
    sf::SoundBuffer         m_winningSoundBuffer;
    sf::Sound               m_winningSound;

    sf::RenderWindow        m_window;

    sf::Clock               m_clock, tenSecondsClock;
    float                   m_timer, m_delay;
    int                     paintedFields;
    int                     calculatePaintedFields();


};
