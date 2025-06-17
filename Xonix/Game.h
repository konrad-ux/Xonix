#pragma once  

#include "Board.h"  
#include "Enemy.h"  
#include "Player.h"  
#include "Bonus.h"  
#include "Teleport.h" 
#include "SpeedBonus.h"
#include "LineImmunityBonus.h" // <-- WAØNE: Dodane do≥πczenie pliku nag≥Ûwkowego

#include <SFML/Graphics.hpp>  
#include <SFML/Window.hpp>  
#include <SFML/Audio.hpp>  

#include <iostream>  
#include <vector>  
#include <string>  
#include <fstream>  
#include <algorithm>  

struct ScoreEntry {
	std::string name;
	int score;
};

class Game
{
public:
	Game();
	void run();

private:
	void handleEvents();
	void draw();
	void checkPlayerTeleportCollision(Player& player, Teleport& teleport1, Teleport& teleport2);
	template<typename TBonus, typename TEffect>
	void checkPlayerBonusCollisionGeneric(Player& player, std::vector<TBonus>& bonuses, TEffect effect);
	int calculatePaintedFields();

	std::vector<ScoreEntry> loadHighScores();
	void showHighScores();
	std::string askPlayerName();
	void saveScoreToFile(const std::string& name, int score);
	int loadLastScoreFromFile();

private:
	Board                  m_board;
	Player                 m_player;
	Teleport               m_teleport1;
	Teleport               m_teleport2;
	std::vector<Enemy>     m_enemies;
	std::vector<Bonus>     m_bonuses;

	// --- Deklaracje dla SpeedBonus ---
	std::vector<SpeedBonus> m_speedBonuses;
	bool m_speedBonusActive = false;
	float m_speedBonusTimer = 0.f;
	const float m_speedBonusDuration = 5.f;
	float m_originalDelay; // Zamiast wskaünika

	// --- Deklaracje dla LineImmunityBonus ---
	std::vector<LineImmunityBonus> m_lineImmunityBonuses;
	bool  m_lineImmunityActive = false;
	float m_lineImmunityTimer = 0.f;
	const float m_lineImmunityDuration = 5.f;

	sf::Texture             m_t1, m_t2, m_t3, m_t4, m_t5, m_t6, m_t7, m_t8; // <-- Dodana m_t8
	sf::Sprite              m_tile, m_gameOver, m_enemy, m_bonus, m_win, s_teleport1, s_teleport2, m_speedBonusSprite, m_lineImmunityBonusSprite; // <-- Dodany sprite
	sf::Font                m_font;
	sf::Text                percentageText;
	sf::SoundBuffer         m_teleportSoundBuffer, m_gameoverSoundBuffer, m_winningSoundBuffer;
	sf::Sound               m_teleportSound, m_gameoverSound, m_winningSound;

	sf::RenderWindow        m_window;

	sf::Clock               m_clock, tenSecondsClock, m_speedBonusClock, m_lineImmunityBonusClock; // <-- Dodany zegar
	float                   m_timer, m_delay;
	int                     paintedFields;

	std::string             m_playerName;
	sf::Texture             m_menuBackgroundTexture;
	sf::Sprite              m_menuBackgroundSprite;
	std::vector<ScoreEntry> m_highScores;
	bool                    m_newHighScore;
	float m_speedBonusSpawnInterval = 20.f;
	float m_lineImmunitySpawnInterval = 25.f; // <-- Dodany interwa≥
};