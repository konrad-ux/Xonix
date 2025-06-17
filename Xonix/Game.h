#pragma once

#include "Board.h"
#include "Enemy.h"
#include "Player.h"
#include "Bonus.h"
#include "Teleport.h"
#include "ResourceManager.h" // Dodaj ten nag³ówek

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <memory>
#include <ostream> // Dodaj ten nag³ówek

struct ScoreEntry {
    std::string name;
    int score = 0;
};

// Deklaracja przeci¹¿onego operatora
std::ostream& operator<<(std::ostream& os, const ScoreEntry& score);

class Game
{
public:
    Game();
    ~Game();
    void run();

    void activateSpeedBonus();
    void activateLineImmunity(Player& player);
    void triggerBombEffect();

private:
    void handleEvents();
    void draw();
    void checkPlayerTeleportCollision(Player& player, Teleport& teleport1, Teleport& teleport2);
    void checkPlayerBonusCollision();
    int calculatePaintedFields();

    std::vector<ScoreEntry> loadHighScores();
    void showHighScores();
    std::string askPlayerName();
    void saveScoreToFile(const std::string& name, int score);

private:
    Board                  m_board;
    Player                 m_player;
    Teleport               m_teleport1;
    Teleport               m_teleport2;
    std::vector<Enemy>     m_enemies;
    std::vector<std::unique_ptr<Bonus>> m_bonuses;

    bool m_speedBonusActive;
    float m_speedBonusTimer;
    const float m_speedBonusDuration;
    float m_originalDelay;

    bool  m_lineImmunityActive;
    float m_lineImmunityTimer;
    const float m_lineImmunityDuration;

    // NOWE MENED¯ERY ZASOBÓW
    ResourceManager<sf::Texture>     m_textureManager;
    ResourceManager<sf::Font>        m_fontManager;
    ResourceManager<sf::SoundBuffer> m_soundManager;

    sf::RenderWindow        m_window;
    // Stare pola na zasoby (t1, t2, font, etc.) zosta³y usuniête
    // Zostawiamy tylko obiekty, które z nich korzystaj¹ (Sprite, Sound, Text)
    sf::Sprite              m_tile, m_gameOver, m_enemy, m_bombSprite, m_win, s_teleport1, s_teleport2, m_speedBonusSprite, m_lineImmunityBonusSprite;
    sf::Sound               m_teleportSound, m_gameoverSound, m_winningSound;
    sf::Sprite              m_menuBackgroundSprite;

    sf::Clock               m_clock, tenSecondsClock, m_speedBonusClock, m_lineImmunityBonusClock, m_bombClock;
    float                   m_timer, m_delay;
    int                     paintedFields;

    std::string             m_playerName;
    std::vector<ScoreEntry> m_highScores;
    bool                    m_newHighScore;

    float m_speedBonusSpawnInterval;
    float m_lineImmunitySpawnInterval;
    float m_bombSpawnInterval;
};