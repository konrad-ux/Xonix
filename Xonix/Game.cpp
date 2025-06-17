#include "Game.h"
#include "menu.h"
#include "SpeedBonus.h"
#include "LineImmunityBonus.h"
#include "Bomb.h"

#include <fstream>
#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <sstream>

// Implementacja przeci¹¿onego operatora dla ScoreEntry (wymaganie "Przeci¹¿enie operatora")
std::ostream& operator<<(std::ostream& os, const ScoreEntry& score) {
    os << score.name << " - " << score.score << "%";
    return os;
}

Game::Game() :
    m_window(sf::VideoMode(WIDTH_SIZE * 18, HEIGHT_SIZE * 18), "Xonix"),
    m_teleport1(0, 10),
    m_teleport2(39, 20),
    m_speedBonusActive(false),
    m_speedBonusTimer(0.f),
    m_speedBonusDuration(5.f),
    m_originalDelay(0.07f),
    m_lineImmunityActive(false),
    m_lineImmunityTimer(0.f),
    m_lineImmunityDuration(5.f),
    m_timer(0.f),
    m_delay(0.07f),
    paintedFields(0),
    m_newHighScore(false),
    m_speedBonusSpawnInterval(20.f),
    m_lineImmunitySpawnInterval(25.f),
    m_bombSpawnInterval(15.f)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    m_window.setFramerateLimit(60);

    // £adowanie zasobów za pomoc¹ klasy generycznej ResourceManager (wymaganie "Klasa generyczna")
    try {
        m_textureManager.load("tileset", "images/solid_tileset.png");
        m_textureManager.load("gameover", "images/gameover.png");
        m_textureManager.load("enemy", "images/duch.png");
        m_textureManager.load("bomb", "images/small_bomb.png");
        m_textureManager.load("win", "images/youwin.png");
        m_textureManager.load("portal", "images/portal.png");
        m_textureManager.load("speed_bonus", "images/apple (2).png");
        m_textureManager.load("immunity_bonus", "images/banana.png");
        m_textureManager.load("menu_bg", "images/background.png");

        m_fontManager.load("main_font", "font/agency_fb_bold.ttf");

        m_soundManager.load("teleport", "sounds/teleport_sound.wav");
        m_soundManager.load("game_over", "sounds/game_over_sound.wav");
        m_soundManager.load("win_sound", "sounds/winning_sound.wav");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error loading resources: " << e.what() << std::endl;
        m_window.close(); // Zamknij okno, jeœli zasoby siê nie za³aduj¹
    }

    // Ustawienie zasobów do obiektów gry
    m_tile.setTexture(m_textureManager.get("tileset"));
    m_gameOver.setTexture(m_textureManager.get("gameover"));
    m_gameOver.setPosition(125.f, 250.f);
    m_win.setTexture(m_textureManager.get("win"));
    m_win.setPosition(100.f, 0.f);
    m_enemy.setTexture(m_textureManager.get("enemy"));
    m_enemy.setOrigin(20.f, 20.f);
    m_bombSprite.setTexture(m_textureManager.get("bomb"));
    m_bombSprite.setOrigin(9.f, 9.f);
    m_speedBonusSprite.setTexture(m_textureManager.get("speed_bonus"));
    m_lineImmunityBonusSprite.setTexture(m_textureManager.get("immunity_bonus"));
    s_teleport1.setTexture(m_textureManager.get("portal"));
    s_teleport2.setTexture(m_textureManager.get("portal"));
    m_menuBackgroundSprite.setTexture(m_textureManager.get("menu_bg"));

    m_teleportSound.setBuffer(m_soundManager.get("teleport"));
    m_teleportSound.setVolume(20);
    m_winningSound.setBuffer(m_soundManager.get("win_sound"));
    m_winningSound.setVolume(30);
    m_gameoverSound.setBuffer(m_soundManager.get("game_over"));
    m_gameoverSound.setVolume(30);

    for (int i = 0; i < 4; ++i) { m_enemies.emplace_back(); }
}

Game::~Game() {}

void Game::activateSpeedBonus() {
    if (!m_speedBonusActive) {
        m_originalDelay = m_delay;
        m_delay = 0.05f;
        m_speedBonusActive = true;
        m_speedBonusTimer = 0.f;
    }
}

void Game::activateLineImmunity(Player& player) {
    if (!m_lineImmunityActive) {
        player.setImmunity(true);
        m_lineImmunityActive = true;
        m_lineImmunityTimer = 0.f;
    }
}

void Game::triggerBombEffect() {
    m_board.reset();
    m_player = Player();
    m_enemies.clear();
    for (int i = 0; i < 4; ++i) {
        m_enemies.emplace_back();
    }
    m_bonuses.clear();
    m_speedBonusClock.restart();
    m_lineImmunityBonusClock.restart();
    m_bombClock.restart();
}

void Game::run() {
    while (m_window.isOpen()) {
        Menu menu(static_cast<float>(m_window.getSize().x), static_cast<float>(m_window.getSize().y));
        bool inMenu = true;

        while (inMenu && m_window.isOpen()) {
            sf::Event event;
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) m_window.close();
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) menu.moveUp();
                    else if (event.key.code == sf::Keyboard::Down) menu.moveDown();
                    else if (event.key.code == sf::Keyboard::Enter) {
                        Menu::MenuOption selected = menu.getSelectedItem();
                        if (selected == Menu::MenuOption::Start) inMenu = false;
                        else if (selected == Menu::MenuOption::HighScores) showHighScores();
                        else if (selected == Menu::MenuOption::Exit) { m_window.close(); return; }
                    }
                }
            }
            m_window.clear();
            menu.draw(m_window);
            m_window.display();
        }

        m_board.reset();
        m_player = Player();
        m_bonuses.clear();
        m_enemies.clear();
        for (int i = 0; i < 4; ++i) m_enemies.emplace_back();

        m_clock.restart(); m_timer = 0.f;
        tenSecondsClock.restart(); m_speedBonusClock.restart(); m_lineImmunityBonusClock.restart(); m_bombClock.restart();

        while (m_window.isOpen() && m_player.isAlive() && !m_player.hasWon()) {
            float time = m_clock.getElapsedTime().asSeconds();
            m_clock.restart();
            m_timer += time;

            handleEvents();

            if (m_bombClock.getElapsedTime().asSeconds() >= m_bombSpawnInterval) {
                m_bonuses.push_back(std::make_unique<Bomb>(rand() % (WIDTH_SIZE - 2) + 1, rand() % (HEIGHT_SIZE - 2) + 1));
                m_bombClock.restart();
            }
            if (m_speedBonusClock.getElapsedTime().asSeconds() >= m_speedBonusSpawnInterval) {
                m_bonuses.push_back(std::make_unique<SpeedBonus>(rand() % (WIDTH_SIZE - 2) + 1, rand() % (HEIGHT_SIZE - 2) + 1));
                m_speedBonusClock.restart();
            }
            if (m_lineImmunityBonusClock.getElapsedTime().asSeconds() >= m_lineImmunitySpawnInterval) {
                m_bonuses.push_back(std::make_unique<LineImmunityBonus>(rand() % (WIDTH_SIZE - 2) + 1, rand() % (HEIGHT_SIZE - 2) + 1));
                m_lineImmunityBonusClock.restart();
            }

            checkPlayerBonusCollision();
            checkPlayerTeleportCollision(m_player, m_teleport1, m_teleport2);

            if (m_speedBonusActive) {
                m_speedBonusTimer += time;
                if (m_speedBonusTimer >= m_speedBonusDuration) { m_delay = m_originalDelay; m_speedBonusActive = false; }
            }
            if (m_lineImmunityActive) {
                m_lineImmunityTimer += time;
                if (m_lineImmunityTimer >= m_lineImmunityDuration) { m_player.setImmunity(false); m_lineImmunityActive = false; }
            }

            m_player.handleInput();
            m_player.move(m_board, m_timer, m_delay);

            for (auto& enemy : m_enemies) { enemy.move(m_board.grid); }

            if (m_board.grid[m_player.getY()][m_player.getX()] == 1) {
                m_player.resetDirection();
                for (const auto& enemy : m_enemies) { m_board.drop(enemy.y / 18, enemy.x / 18); }
                m_board.finalize();
            }
            for (const auto& enemy : m_enemies) { if (m_board.grid[enemy.y / 18][enemy.x / 18] == 2) { m_player.setAlive(false); } }
            draw();
        }

        if (!m_player.isAlive()) m_gameoverSound.play();
        else if (m_player.hasWon()) m_winningSound.play();

        sf::Clock endClock;
        while (endClock.getElapsedTime().asSeconds() < 2.0f && m_window.isOpen()) { m_window.clear(); draw(); m_window.display(); }

        if (m_player.hasWon() || !m_player.isAlive()) {
            m_playerName = askPlayerName();
            if (!m_playerName.empty()) { saveScoreToFile(m_playerName, calculatePaintedFields()); }
        }
    }
}

void Game::handleEvents() {
    sf::Event event{};
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) m_window.close();
    }
}

void Game::draw() {
    m_window.clear();
    for (int i = 0; i < HEIGHT_SIZE; ++i) {
        for (int j = 0; j < WIDTH_SIZE; ++j) {
            if (m_board.grid[i][j] == 0) continue;
            if (m_board.grid[i][j] == 1) m_tile.setTextureRect(sf::IntRect(0, 36, 18, 18));
            if (m_board.grid[i][j] == 2) m_tile.setTextureRect(sf::IntRect(0, 90, 18, 18));
            m_tile.setPosition(static_cast<float>(j * 18), static_cast<float>(i * 18));
            m_window.draw(m_tile);
        }
    }

    for (const auto& bonus : m_bonuses) {
        sf::Sprite* bonusSprite = nullptr;
        if (dynamic_cast<Bomb*>(bonus.get())) {
            bonusSprite = &m_bombSprite;
        }
        else if (dynamic_cast<SpeedBonus*>(bonus.get())) {
            bonusSprite = &m_speedBonusSprite;
        }
        else if (dynamic_cast<LineImmunityBonus*>(bonus.get())) {
            bonusSprite = &m_lineImmunityBonusSprite;
        }
        if (bonusSprite) {
            bonusSprite->setPosition(static_cast<float>(bonus->getX() * 18), static_cast<float>(bonus->getY() * 18));
            m_window.draw(*bonusSprite);
        }
    }

    s_teleport1.setPosition(static_cast<float>(m_teleport1.getX() * 18), static_cast<float>(m_teleport1.getY() * 18));
    m_window.draw(s_teleport1);
    s_teleport2.setPosition(static_cast<float>(m_teleport2.getX() * 18), static_cast<float>(m_teleport2.getY() * 18));
    m_window.draw(s_teleport2);

    m_tile.setTextureRect(sf::IntRect(0, 18, 18, 18));
    m_tile.setPosition(static_cast<float>(m_player.getX() * 18), static_cast<float>(m_player.getY() * 18));
    m_window.draw(m_tile);

    sf::RectangleShape blackBar(sf::Vector2f(155.f, 47.f));
    blackBar.setFillColor(sf::Color::Black);
    blackBar.setOutlineColor(sf::Color::Red);
    blackBar.setOutlineThickness(3.f);
    blackBar.setPosition(3.f, 3.f);
    m_window.draw(blackBar);

    paintedFields = calculatePaintedFields();
    sf::Text paintedFieldsText;
    paintedFieldsText.setFont(m_fontManager.get("main_font"));
    paintedFieldsText.setCharacterSize(35);
    paintedFieldsText.setFillColor(sf::Color::White);
    paintedFieldsText.setStyle(sf::Text::Bold);
    paintedFieldsText.setString("Score: " + std::to_string(paintedFields) + "%");
    paintedFieldsText.setPosition(18.f, 6.f);
    m_window.draw(paintedFieldsText);

    m_enemy.rotate(5);
    for (const auto& enemy : m_enemies) {
        m_enemy.setPosition(static_cast<float>(enemy.x), static_cast<float>(enemy.y));
        m_window.draw(m_enemy);
    }
    if (!m_player.isAlive()) m_window.draw(m_gameOver);
    if (m_player.hasWon()) m_window.draw(m_win);
    m_window.display();
}

void Game::checkPlayerBonusCollision() {
    sf::FloatRect playerBounds = m_player.getBounds();
    auto it = m_bonuses.begin();
    while (it != m_bonuses.end()) {
        if (playerBounds.intersects((*it)->getBounds())) {
            bool isBomb = (dynamic_cast<Bomb*>(it->get()) != nullptr);
            (*it)->applyEffect(m_player, *this);
            if (isBomb) {
                break;
            }
            else {
                it = m_bonuses.erase(it);
            }
        }
        else {
            ++it;
        }
    }
}

void Game::checkPlayerTeleportCollision(Player& player, Teleport& teleport1, Teleport& teleport2) {
    static bool isTeleported = false;
    bool isInPortal1 = player.getX() == teleport1.getX() && player.getY() == teleport1.getY();
    bool isInPortal2 = player.getX() == teleport2.getX() && player.getY() == teleport2.getY();
    if (!isTeleported && isInPortal1) {
        isTeleported = true;
        player.setPosition(teleport2.getX(), teleport2.getY());
        m_teleportSound.play();
    }
    else if (!isTeleported && isInPortal2) {
        isTeleported = true;
        player.setPosition(teleport1.getX(), teleport1.getY());
        m_teleportSound.play();
    }
    else if (isTeleported && !(isInPortal1 || isInPortal2)) {
        isTeleported = false;
    }
}

int Game::calculatePaintedFields() {
    float paintedCount = -27;
    float totalCount = ((WIDTH_SIZE - 2) * (HEIGHT_SIZE - 2)) - 27;
    for (int i = 1; i < HEIGHT_SIZE - 1; ++i) {
        for (int j = 1; j < WIDTH_SIZE - 1; ++j) {
            if (m_board.grid[i][j] == 1) ++paintedCount;
        }
    }
    int score = static_cast<int>((paintedCount / totalCount) * 100);
    if (score >= 80) m_player.setWin(true);
    return score > 0 ? score : 0;
}

void Game::saveScoreToFile(const std::string& name, int score) {
    std::ofstream file("score.txt", std::ios::app);
    if (file.is_open()) { file << name << " - " << score << "%" << std::endl; }
    else { std::cerr << "Nie mo¿na zapisaæ wyniku do pliku!" << std::endl; }
}

std::string Game::askPlayerName() {
    sf::Text prompt, inputText;
    prompt.setFont(m_fontManager.get("main_font"));
    inputText.setFont(m_fontManager.get("main_font"));
    prompt.setCharacterSize(45); inputText.setCharacterSize(40);
    prompt.setFillColor(sf::Color::White); inputText.setFillColor(sf::Color::Yellow);
    prompt.setString("Enter your name:");
    prompt.setPosition(230.f, 350.f); inputText.setPosition(300.f, 450.f);
    std::string input;
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { m_window.close(); return ""; }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !input.empty()) { input.pop_back(); }
                else if (event.text.unicode >= 32 && event.text.unicode < 128 && input.size() < 15) {
                    input += static_cast<char>(event.text.unicode);
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter && !input.empty()) { return input; }
                if (event.key.code == sf::Keyboard::Escape) { return ""; }
            }
        }
        inputText.setString(input);
        m_window.clear();
        m_window.draw(m_menuBackgroundSprite);
        m_window.draw(prompt);
        m_window.draw(inputText);
        m_window.display();
    }
    return "";
}

std::vector<ScoreEntry> Game::loadHighScores() {
    std::ifstream file("score.txt");
    std::vector<ScoreEntry> all;
    std::string line;
    while (std::getline(file, line)) {
        auto dashPos = line.find(" - ");
        auto percPos = line.find('%');
        if (dashPos != std::string::npos && percPos != std::string::npos) {
            std::string name = line.substr(0, dashPos);
            int score = std::stoi(line.substr(dashPos + 3, percPos - (dashPos + 3)));
            all.push_back({ name, score });
        }
    }
    std::sort(all.begin(), all.end(), [](const ScoreEntry& a, const ScoreEntry& b) { return a.score > b.score; });
    if (all.size() > 5) all.resize(5);
    return all;
}

void Game::showHighScores() {
    auto highs = loadHighScores();
    std::vector<sf::Text> texts;
    sf::Text title;
    title.setFont(m_fontManager.get("main_font"));
    title.setCharacterSize(70);
    title.setFillColor(sf::Color::White);
    title.setString("Top 5");
    sf::FloatRect textRect = title.getLocalBounds();
    title.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    title.setPosition(m_window.getSize().x / 2.0f, 330.f);
    texts.push_back(title);

    for (size_t i = 0; i < highs.size(); ++i) {
        sf::Text t;
        t.setFont(m_fontManager.get("main_font"));
        t.setCharacterSize(35);
        t.setFillColor(sf::Color::White);

        std::stringstream ss;
        ss << i + 1 << ". " << highs[i]; // U¿ycie przeci¹¿onego operatora
        t.setString(ss.str());

        t.setPosition(250.f, 390.f + static_cast<float>(i * 50));
        texts.push_back(t);
    }

    sf::Text back;
    back.setFont(m_fontManager.get("main_font"));
    back.setCharacterSize(25);
    back.setFillColor(sf::Color::Yellow);
    back.setString("Wcisnij Esc lub Enter, aby wrocic");
    sf::FloatRect backRect = back.getLocalBounds();
    back.setOrigin(backRect.left + backRect.width / 2.0f, backRect.top + backRect.height / 2.0f);
    back.setPosition(m_window.getSize().x / 2.0f, 670.f);

    bool showingScores = true;
    while (m_window.isOpen() && showingScores) {
        sf::Event ev;
        while (m_window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) m_window.close();
            if (ev.type == sf::Event::KeyPressed && (ev.key.code == sf::Keyboard::Escape || ev.key.code == sf::Keyboard::Enter)) {
                showingScores = false;
            }
        }
        m_window.clear();
        m_window.draw(m_menuBackgroundSprite);
        for (auto& t : texts) m_window.draw(t);
        m_window.draw(back);
        m_window.display();
    }
}

int Game::loadLastScoreFromFile() {
    return 0; // Ta metoda nie jest u¿ywana, mo¿na j¹ zaimplementowaæ w przysz³oœci
}