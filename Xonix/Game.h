#pragma once

#include "Board.h"
#include "Enemy.h"
#include "Player.h"
#include "Bonus.h"
#include "Teleport.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <memory>
#include <ostream>

struct ScoreEntry {
    std::string name;
    int score = 0;
};

std::ostream& operator<<(std::ostream& os, const ScoreEntry& score);

class Game {
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
    void saveScoreToFile(const std::string& name, int score);
    std::string askPlayerName();
    void showHighScores();
    std::vector<ScoreEntry> loadHighScores();

    Board m_board;
    Player m_player;
    Teleport m_teleport1;
    Teleport m_teleport2;
    std::vector<Enemy> m_enemies;
    std::vector<std::unique_ptr<Bonus>> m_bonuses;

    bool m_speedBonusActive;
    float m_speedBonusTimer;
    const float m_speedBonusDuration;
    float m_originalDelay;

    bool m_showEasterEgg;
    bool m_lineImmunityActive;
    float m_lineImmunityTimer;
    const float m_lineImmunityDuration;

    ResourceManager<sf::Texture> m_textureManager;
    ResourceManager<sf::Font> m_fontManager;
    ResourceManager<sf::SoundBuffer> m_soundManager;

    sf::RenderWindow m_window;
    sf::Sprite m_tile;
    sf::Sprite m_gameOver;
    sf::Sprite m_enemy;
    sf::Sprite m_bombSprite;
    sf::Sprite m_win;
    sf::Sprite s_teleport1;
    sf::Sprite s_teleport2;
    sf::Sprite m_speedBonusSprite;
    sf::Sprite m_lineImmunityBonusSprite;
    sf::Sprite m_menuBackgroundSprite;
    sf::Sprite m_easterEggSprite;

    sf::Sound m_teleportSound;
    sf::Sound m_gameoverSound;
    sf::Sound m_winningSound;

    sf::Clock m_clock;
    sf::Clock tenSecondsClock;
    sf::Clock m_speedBonusClock;
    sf::Clock m_lineImmunityBonusClock;
    sf::Clock m_bombClock;

    float m_timer;
    float m_delay;
    int paintedFields;

    std::string m_playerName;
    std::vector<ScoreEntry> m_highScores;
    bool m_newHighScore;

    float m_speedBonusSpawnInterval;
    float m_lineImmunitySpawnInterval;
    float m_bombSpawnInterval;
};