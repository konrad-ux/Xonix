#pragma once  

#include "Board.h"  
#include "Enemy.h"  
#include "Player.h"  
#include "Bonus.h"  
#include "Teleport.h" 
#include "SpeedBonus.h"

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
	//void checkPlayerBonusCollision(Player& player);
	//void checkPlayerSpeedBonusCollision(Player& m_player);
	void checkPlayerTeleportCollision(Player& player, Teleport& teleport1, Teleport& teleport2);
	template<typename TBonus, typename TEffect>
	void checkPlayerBonusCollisionGeneric(Player& player, std::vector<TBonus>& bonuses, TEffect effect);
	int calculatePaintedFields();

	std::vector<ScoreEntry> loadHighScores();    // �aduje i sortuje top 5
	void showHighScores();
	// --- Nowe funkcje do obs�ugi wyniku ---  
	std::string askPlayerName();
	void saveScoreToFile(const std::string& name, int score);
	int loadLastScoreFromFile(); // Deklaracja brakuj�cej funkcji  

private:
	Board                  m_board;
	Player                  m_player;
	Teleport                m_teleport1;
	Teleport                m_teleport2;
	SpeedBonus* m_activeSpeedBonus = nullptr;
	std::vector<Enemy>      m_enemies;
	std::vector<Bonus>      m_bonuses;
	std::vector<SpeedBonus> m_speedBonuses;
	bool m_speedBonusActive = false;
	float m_speedBonusTimer = 0.f;
	float m_speedBonusDuration = 5.f;

	sf::Texture             m_t1, m_t2, m_t3, m_t4, m_t5, m_t6, m_t7;
	sf::Sprite              m_tile, m_gameOver, m_enemy, m_bonus, m_win, s_teleport1, s_teleport2, m_speedBonusSprite;
	sf::Font                m_font;
	sf::Text                percentageText;
	sf::SoundBuffer         m_teleportSoundBuffer;
	sf::Sound               m_teleportSound;
	sf::SoundBuffer         m_gameoverSoundBuffer;
	sf::Sound               m_gameoverSound;
	sf::SoundBuffer         m_winningSoundBuffer;
	sf::Sound               m_winningSound;

	sf::RenderWindow        m_window;

	sf::Clock               m_clock, tenSecondsClock, m_speedBonusClock;
	float                   m_timer, m_delay;
	int                     paintedFields;

	std::string             m_playerName;             // <-- przechowywanie imienia  
	sf::Texture             m_menuBackgroundTexture;
	sf::Sprite              m_menuBackgroundSprite;
	std::vector<ScoreEntry> m_highScores;
	bool                    m_newHighScore;
	float m_speedBonusSpawnInterval = 15.f;
};
