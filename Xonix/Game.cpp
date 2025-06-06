#include "Game.h"
#include "menu.h"
#include <fstream>
#include <algorithm> 

Game::Game() :
    m_window(sf::VideoMode(WIDTH_SIZE * 18, HEIGHT_SIZE * 18), "Xonix"),
    m_timer(0), m_delay(0.07), m_teleport1(0, 10), m_teleport2(39, 20)
{
    srand(time(nullptr));
    m_window.setFramerateLimit(60);

    m_t1.loadFromFile("images/solid_tileset.png");
    m_t2.loadFromFile("images/gameover.png");
    m_t3.loadFromFile("images/duch.png");
    m_t4.loadFromFile("images/small_bomb.png");
    m_t5.loadFromFile("images/youwin.png");
    m_t6.loadFromFile("images/portal.png");
	m_t7.loadFromFile("images/apple (2).png");

    if (!m_menuBackgroundTexture.loadFromFile("images/menu3.png")) {
        std::cerr << "B³¹d ³adowania t³a menu3.png\n";
    }
    m_menuBackgroundSprite.setTexture(m_menuBackgroundTexture);

    if (!m_teleportSoundBuffer.loadFromFile("sounds/teleport_sound.wav")){
        std::cerr << "Nie udalo sie zaladowac pliku dzwiekowego teleport.wav!" << std::endl;
    }
    m_teleportSound.setBuffer(m_teleportSoundBuffer);
    m_teleportSound.setVolume(20);

    if (!m_winningSoundBuffer.loadFromFile("sounds/winning_sound.wav")) {
        std::cerr << "Nie udalo sie zaladowac pliku dzwiekowego winning.wav!" << std::endl;
    }
    m_winningSound.setBuffer(m_winningSoundBuffer);
    m_winningSound.setVolume(30);

    if (!m_gameoverSoundBuffer.loadFromFile("sounds/game_over_sound.wav")) {
        std::cerr << "Nie udalo sie zaladowac pliku dzwiekowego game_over_sound.wav!" << std::endl;
    }
    m_gameoverSound.setBuffer(m_gameoverSoundBuffer);
    m_gameoverSound.setVolume(30);

    m_tile.setTexture(m_t1);
    m_gameOver.setTexture(m_t2);
    m_gameOver.setPosition(100, 100);
    m_win.setTexture(m_t5);
    m_win.setPosition(100, 0);
    m_enemy.setTexture(m_t3);
    m_enemy.setOrigin(20, 20);
    m_bonus.setTexture(m_t4);
    m_bonus.setOrigin(9, 9);
	m_speedBonusSprite.setTexture(m_t7);
    s_teleport1.setTexture(m_t6);
    s_teleport2.setTexture(m_t6);

    if (!m_font.loadFromFile("font/agency_fb_bold.ttf")) {
        std::cerr << "Nie udalo sie zaladowac czcionki!" << std::endl;
    }

    for (int i = 0; i < 4; ++i) {
        m_enemies.emplace_back();
    }
}

void Game::run() {
    while (m_window.isOpen()) {
        Menu menu(m_window.getSize().x, m_window.getSize().y);
        bool inMenu = true;

        while (inMenu && m_window.isOpen()) {
            sf::Event event;
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    m_window.close();

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up)
                        menu.moveUp();
                    else if (event.key.code == sf::Keyboard::Down)
                        menu.moveDown();
                    else if (event.key.code == sf::Keyboard::Enter) {
                        int selected = menu.getSelectedItemIndex();
                        if (selected == 0) {
                            inMenu = false;          // START
                        }
                        else if (selected == 1) {
                            showHighScores();        // TABLICA WYNIKÓW
                        }
                        else if (selected == 2) {
                            m_window.close();        // zamykamy okno SFML                 // wychodzimy z Game::run(), koñczymy program
                            return;
                        }
                    }
                }
            }

            m_window.clear();
            menu.draw(m_window);
            m_window.display();
        }

        // Rozpoczêcie gry...
        m_board.reset();
        m_player = Player();
        m_bonuses.clear();
		m_speedBonuses.clear();
        m_enemies.clear();
        for (int i = 0; i < 4; ++i)
            m_enemies.emplace_back();

        m_player.alive = true;
        m_player.win = false;
        m_clock.restart();
        m_timer = 0;

        while (m_window.isOpen() && m_player.alive && !m_player.win) {
            const float time = m_clock.getElapsedTime().asSeconds();
            m_clock.restart();
            m_timer += time;
            handleEvents();
            if (tenSecondsClock.getElapsedTime().asSeconds() >= 7) {
                int randomX = rand() % (WIDTH_SIZE - 2) + 1;
                int randomY = rand() % (HEIGHT_SIZE - 2) + 1;
                m_bonuses.emplace_back(randomX, randomY);
                tenSecondsClock.restart();
            }

            if (m_speedBonusClock.getElapsedTime().asSeconds() >= m_speedBonusSpawnInterval) {
                int randomX = rand() % (WIDTH_SIZE - 2) + 1;
                int randomY = rand() % (HEIGHT_SIZE - 2) + 1;
                m_speedBonuses.emplace_back(randomX, randomY);
                m_speedBonusClock.restart();
            }



            checkPlayerBonusCollision(m_player);
            checkPlayerSpeedBonusCollision(m_player);
            checkPlayerTeleportCollision(m_player, m_teleport1, m_teleport2);

            m_player.handleInput();
            m_player.move(m_board, m_timer, m_delay);

            for (auto& enemy : m_enemies) {
                enemy.move(m_board.grid);
            }

            if (m_board.grid[m_player.y][m_player.x] == 1) {
                m_player.dx = m_player.dy = 0;
                for (const auto& enemy : m_enemies) {
                    m_board.drop(enemy.y / 18, enemy.x / 18);
                }
                m_board.finalize();
            }

            for (const auto& enemy : m_enemies) {
                if (m_board.grid[enemy.y / 18][enemy.x / 18] == 2) {
                    m_player.alive = false;
                }
            }

            draw();
        }
        if (!m_player.alive) {
            m_gameoverSound.play();
        }
        else if (m_player.win) {
            m_winningSound.play();
        }


        // Ekran GAME OVER/WIN i zapis wyniku
        sf::Clock endClock;
        while (endClock.getElapsedTime().asSeconds() < 2.0f && m_window.isOpen()) {
            m_window.clear();
            draw();
            m_window.display();
        }

        m_playerName = askPlayerName();
        saveScoreToFile(m_playerName, calculatePaintedFields());
    }
}

void Game::handleEvents() {
    sf::Event event{};
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            m_board.reset();
            m_player = Player();
        }
    }
}

void Game::draw() {
    m_window.clear();

    for (int i = 0; i < HEIGHT_SIZE; ++i) {
        for (int j = 0; j < WIDTH_SIZE; ++j) {
            if (m_board.grid[i][j] == 0)
                continue;
            if (m_board.grid[i][j] == 1)
                m_tile.setTextureRect(sf::IntRect(0, 36, 18, 18));
            if (m_board.grid[i][j] == 2)
                m_tile.setTextureRect(sf::IntRect(0, 90, 18, 18));

            m_tile.setPosition(j * 18, i * 18);
            m_window.draw(m_tile);
        }
    }

    for (const auto& bonus : m_bonuses) {
        m_bonus.setPosition(bonus.getX() * 18, bonus.getY() * 18);
        m_window.draw(m_bonus);
    }

    s_teleport1.setPosition(m_teleport1.m_x * 18, m_teleport1.m_y * 18);
    m_window.draw(s_teleport1);

    s_teleport2.setPosition(m_teleport2.m_x * 18, m_teleport2.m_y * 18);
    m_window.draw(s_teleport2);

    m_tile.setTextureRect(sf::IntRect(0, 18, 18, 18));
    m_tile.setPosition(m_player.x * 18, m_player.y * 18);
    m_window.draw(m_tile);

    sf::RectangleShape blackBar(sf::Vector2f(155.f, 47.f));
    blackBar.setFillColor(sf::Color::Black);
    blackBar.setOutlineColor(sf::Color::Red);
    blackBar.setOutlineThickness(3.f);
    blackBar.setPosition(3.f, 3.f);
    m_window.draw(blackBar);

    paintedFields = calculatePaintedFields();

    sf::Text paintedFieldsText;
    paintedFieldsText.setFont(m_font);
    paintedFieldsText.setCharacterSize(35);
    paintedFieldsText.setFillColor(sf::Color::White);
    paintedFieldsText.setStyle(sf::Text::Bold);
    paintedFieldsText.setString("Score: " + std::to_string(paintedFields) + "%");
    paintedFieldsText.setPosition(18.f, 6.f);
    m_window.draw(paintedFieldsText);

    // Wyœwietlenie ostatniego zapisanego wyniku
    int lastScore = Game::loadLastScoreFromFile();
    sf::Text lastScoreText;
    lastScoreText.setFont(m_font);
    lastScoreText.setCharacterSize(18);
    lastScoreText.setFillColor(sf::Color::Yellow);
    lastScoreText.setStyle(sf::Text::Bold);
    lastScoreText.setString("Last: " + std::to_string(lastScore) + "%");
    lastScoreText.setPosition(18.f, 42.f);
    m_window.draw(lastScoreText);

    m_enemy.rotate(5);
    for (const auto& enemy : m_enemies) {
        m_enemy.setPosition(enemy.x, enemy.y);
        m_window.draw(m_enemy);
    }

    for (const auto& speedBonus : m_speedBonuses) {
        m_speedBonusSprite.setPosition(speedBonus.getX() * 18, speedBonus.getY() * 18);
        m_window.draw(m_speedBonusSprite);
    }

    if (!m_player.alive) {
        m_window.draw(m_gameOver);
    }

    if (m_player.win) {
        m_window.draw(m_win);
        m_winningSound.play();
        m_player.alive = 0;
    }

    m_window.display();
}

int Game::calculatePaintedFields() {
    float paintedCount = -27;
    float totalCount = ((WIDTH_SIZE - 2) * (HEIGHT_SIZE - 2)) - 27;

    for (int i = 1; i < HEIGHT_SIZE - 1; ++i) {
        for (int j = 1; j < WIDTH_SIZE - 1; ++j) {
            if (m_board.grid[i][j] == 1)
                ++paintedCount;
        }
    }

    float result = paintedCount / totalCount;
    int score = static_cast<int>(result * 100);

    if (score >= 80)
        m_player.win = true;

    return score;
}

void Game::checkPlayerBonusCollision(Player& player) {
    sf::FloatRect playerBounds = m_tile.getGlobalBounds();

    for (auto it = m_bonuses.begin(); it != m_bonuses.end(); ) {
        m_bonus.setPosition(it->getX() * 18, it->getY() * 18);
        sf::FloatRect bonusBounds = m_bonus.getGlobalBounds();

        if (playerBounds.intersects(bonusBounds)) {
            m_board.reset();
            m_player = Player();
            m_gameoverSound.play();
            m_bonuses.clear();
            break;
        }
        else {
            ++it;
        }
    }
}

void Game::checkPlayerTeleportCollision(Player& player, Teleport& teleport1, Teleport& teleport2) {
    static bool isTeleported = false;
    bool isInPortal1 = player.x == teleport1.m_x && player.y == teleport1.m_y;
    bool isInPortal2 = player.x == teleport2.m_x && player.y == teleport2.m_y;

    if (!isTeleported && isInPortal1) {
        isTeleported = true;
        player.x = teleport2.m_x;
        player.y = teleport2.m_y;
        m_teleportSound.play();
    }
    else if (!isTeleported && isInPortal2) {
        isTeleported = true;
        player.x = teleport1.m_x;
        player.y = teleport1.m_y;
        m_teleportSound.play();
    }
    else if (isTeleported && !(isInPortal1 || isInPortal2)) {
        isTeleported = false;
    }
}

void Game::checkPlayerSpeedBonusCollision(Player& player) {
    sf::FloatRect playerBounds(player.x * 18, player.y * 18, 18, 18);

    // Handle active speed bonus effect
    if (m_speedBonusActive) {
        m_speedBonusTimer += m_clock.getElapsedTime().asSeconds();
        if (m_speedBonusTimer >= m_speedBonusDuration) {
            if (m_activeSpeedBonus) {
                m_activeSpeedBonus->resetSpeedBonus(player);
                m_activeSpeedBonus = nullptr;
            }
            m_speedBonusActive = false;
            m_speedBonusTimer = 0.f;
        }
        return;
    }

    // Check collision with any available speed bonus
    for (auto it = m_speedBonuses.begin(); it != m_speedBonuses.end(); ++it) {
        sf::FloatRect bonusBounds(it->getX() * 18, it->getY() * 18, 18, 18);
        if (playerBounds.intersects(bonusBounds)) {
            it->applySpeedBonus(player);
            m_speedBonusActive = true;
            m_speedBonusTimer = 0.f;
            m_activeSpeedBonus = &(*it);
            // Optionally play a sound here, e.g. m_speedBonusSound.play();
            m_speedBonuses.erase(it); // Remove the bonus from the board
            break;
        }
    }
}

void Game::saveScoreToFile(const std::string& name, int score)
{
    std::ofstream file("score.txt", std::ios::app);
    if (file.is_open()) {
        file << name << " - " << score << "%" << std::endl;
        file.close();
    }
    else {
        std::cerr << "Nie mo¿na zapisaæ wyniku do pliku!" << std::endl;
    }
}

int Game::loadLastScoreFromFile() {
    std::ifstream file("score.txt");
    std::string line;
    int score = 0;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            // czytamy wszystkie linie, ostatnia zostanie w 'line'
        }
        file.close();

        if (!line.empty()) {
            size_t dashPos = line.find('-');
            size_t percentPos = line.find('%');
            if (dashPos != std::string::npos && percentPos != std::string::npos) {
                std::string scoreStr = line.substr(dashPos + 1, percentPos - dashPos - 1);
                try {
                    score = std::stoi(scoreStr);
                }
                catch (...) {
                    score = 0; // w razie b³êdu konwersji
                }
            }
        }
    }

    return score;
}

std::string Game::askPlayerName()
{
    sf::Text prompt;
    prompt.setFont(m_font);
    prompt.setCharacterSize(30);
    prompt.setFillColor(sf::Color::White);
    prompt.setString("Podaj imiê:");
    prompt.setPosition(150.f, 200.f);

    sf::Text inputText;
    inputText.setFont(m_font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(sf::Color::Yellow);
    inputText.setPosition(150.f, 250.f);

    std::string input;

    while (true) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !input.empty()) {
                    input.pop_back(); // Backspace
                }
                else if (event.text.unicode == '\r') {
                    return input; // Enter pressed
                }
                else if (event.text.unicode < 128 && input.size() < 15) {
                    input += static_cast<char>(event.text.unicode);
                }
            }
        }

        inputText.setString(input);

        m_window.clear();
        m_window.draw(m_menuBackgroundSprite);
        m_window.draw(prompt);
        m_window.draw(inputText);
        m_window.display();
    }
}

std::vector<ScoreEntry> Game::loadHighScores() {
    std::ifstream file("score.txt");
    std::vector<ScoreEntry> all;
    std::string line;

    while (std::getline(file, line)) {
        auto dashPos = line.find('-');
        auto percPos = line.find('%');
        if (dashPos != std::string::npos && percPos != std::string::npos) {
            std::string name = line.substr(0, dashPos - 1);
            int score = std::stoi(line.substr(dashPos + 2, percPos - dashPos - 2));
            all.push_back({ name, score });
        }
    }
    std::sort(all.begin(), all.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
        });
    if (all.size() > 5) all.resize(5);
    return all;
}

void Game::showHighScores() {
    auto highs = loadHighScores();
    std::vector<sf::Text> texts;

    sf::Text title;
    title.setFont(m_font);
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setString("Top 5");
    title.setPosition(320, 100);
    texts.push_back(title);

    for (size_t i = 0; i < highs.size(); ++i) {
        sf::Text t;
        t.setFont(m_font);
        t.setCharacterSize(35);
        t.setFillColor(sf::Color::White);
        t.setString(
            std::to_string(i + 1) + ". " + highs[i].name + " - " + std::to_string(highs[i].score) + "%"
        );
        t.setPosition(150, 180 + i * 50);
        texts.push_back(t);
    }

    sf::Text back;
    back.setFont(m_font);
    back.setCharacterSize(25);
    back.setFillColor(sf::Color::Yellow);
    back.setString("Wcisnij Esc lub Enter, aby wrocic");
    back.setPosition(100, 450);

    // Pêtla wyœwietlania
    while (m_window.isOpen()) {
        sf::Event ev;
        while (m_window.pollEvent(ev)) {
            if (ev.type == sf::Event::KeyPressed &&
                (ev.key.code == sf::Keyboard::Escape || ev.key.code == sf::Keyboard::Enter))
            {
                return; // powrót do menu
            }
            if (ev.type == sf::Event::Closed)
                m_window.close();
        }
        m_window.clear();
        m_window.clear();
        // najpierw t³o takie samo jak w menu
        m_window.draw(m_menuBackgroundSprite);
        for (auto& t : texts)
            m_window.draw(t);
        m_window.draw(back);
        m_window.display();
    }
}