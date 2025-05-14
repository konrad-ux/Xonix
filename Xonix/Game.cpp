#include "Game.h"
#include "menu.h"

Game::Game() :
    m_window(sf::VideoMode(WIDTH_SIZE * 18, HEIGHT_SIZE * 18), "Xonix"),
    m_timer(0), m_delay(0.07), m_teleport1(0, 10), m_teleport2(39, 20)
{
    srand(time(nullptr));
    m_window.setFramerateLimit(60);


    m_t1.loadFromFile("solid_tileset.png");
    m_t2.loadFromFile("gameover.png");
    m_t3.loadFromFile("duch.png");
    m_t4.loadFromFile("small_bomb.png");
    m_t5.loadFromFile("youwin.png");
    m_t6.loadFromFile("portal.png");



    if (!m_teleportSoundBuffer.loadFromFile("teleport_sound.wav")) {
        std::cerr << "Nie udal sie zaladowac pliku dzwiekowego teleport.wav!" << std::endl;
    }
    m_teleportSound.setBuffer(m_teleportSoundBuffer);
    m_teleportSound.setVolume(20);

    if (!m_winningSoundBuffer.loadFromFile("winning_sound.wav")) {
        std::cerr << "Nie udalo sie zaladowac pliku dzwiekowego winning.wav!" << std::endl;
    }
    m_winningSound.setBuffer(m_winningSoundBuffer);
    m_winningSound.setVolume(30);

    if (!m_gameoverSoundBuffer.loadFromFile("game_over_sound.wav")) {
        std::cerr << "Nie udalo sie zaladowac pliku dzwiekowego game_over_sound.wav!" << std::endl;
    }
    m_gameoverSound.setBuffer(m_gameoverSoundBuffer);
    m_gameoverSound.setVolume(30);



    m_tile.setTexture(m_t1);
    m_gameOver.setTexture(m_t2);
    m_gameOver.setPosition(100, 100);
    m_win.setTexture(m_t5);
    m_win.setPosition(100, 00);
    m_enemy.setTexture(m_t3);
    m_enemy.setOrigin(20, 20);
    m_bonus.setTexture(m_t4);
    m_bonus.setOrigin(9, 9);
    s_teleport1.setTexture(m_t6);
    s_teleport2.setTexture(m_t6);



    if (!m_font.loadFromFile("agency_fb.ttf")) // sciezka do pliku czcionki
    {
        std::cerr << "Nie udalo sie zaladowac czcionki!" << std::endl;
    }



    for (int i = 0; i < 4; ++i)            //dodajemy obiekty enemy
    {
        m_enemies.emplace_back();
    }
}

void Game::run() {
    while (m_window.isOpen()) {
        // ----------- MENU ----------
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
                        if (selected == 0) { // Start Game
                            inMenu = false;
                        }
                        else if (selected == 1) { // Exit
                            m_window.close();
                        }
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
        for (int i = 0; i < 4; ++i) {
            m_enemies.emplace_back();
        }
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

            checkPlayerBonusCollision(m_player);
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

        // ----------- GAME OVER / WIN -----------
        sf::Clock endClock;
        while (endClock.getElapsedTime().asSeconds() < 3.0f && m_window.isOpen()) {
            m_window.clear();
            draw();
            m_window.display();
        }

    }
}


void Game::handleEvents()
{
    sf::Event event{};

    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            m_board.reset();
            m_player = Player();
        }
    }
}

void Game::draw()
{
    m_window.clear();

    for (int i = 0; i < HEIGHT_SIZE; ++i)          //ustawianie tekstur dla tablicy
    {
        for (int j = 0; j < WIDTH_SIZE; ++j)
        {
            if (m_board.grid[i][j] == 0)
            {
                continue;
            }

            if (m_board.grid[i][j] == 1)
            {
                m_tile.setTextureRect(sf::IntRect(0, 36, 18, 18));            //tekstura dla scian
            }

            if (m_board.grid[i][j] == 2)
            {
                m_tile.setTextureRect(sf::IntRect(0, 90, 18, 18));        //tekstura dla sladu gracza
            }

            m_tile.setPosition(j * 18, i * 18);       //rysowanie kafelkow
            m_window.draw(m_tile);
        }
    }


    // Rysowanie bomb
    for (const auto& bonus : m_bonuses)
    {
        m_bonus.setPosition(bonus.getX() * 18, bonus.getY() * 18);
        m_window.draw(m_bonus);
    }

    s_teleport1.setPosition(m_teleport1.m_x * 18, m_teleport1.m_y * 18);
    m_window.draw(s_teleport1);

    s_teleport2.setPosition(m_teleport2.m_x * 18, m_teleport2.m_y * 18);
    m_window.draw(s_teleport2);



    //ustawianie tekstury,pozycji i rysowanie gracza
    m_tile.setTextureRect(sf::IntRect(0, 18, 18, 18));
    m_tile.setPosition(m_player.x * 18, m_player.y * 18);
    m_window.draw(m_tile);


    //rysowanie tabeli wynikow
    sf::RectangleShape blackBar(sf::Vector2f(155.f, 47.f));
    blackBar.setFillColor(sf::Color::Black);
    blackBar.setOutlineColor(sf::Color::Red);
    blackBar.setOutlineThickness(3.f);
    blackBar.setPosition(3.f, 3.f);
    m_window.draw(blackBar);





    paintedFields = calculatePaintedFields(); // Obliczenie zamalowanych pól

    //wypisywanie wynikow
    sf::Text paintedFieldsText;
    paintedFieldsText.setFont(m_font);
    paintedFieldsText.setCharacterSize(35);
    paintedFieldsText.setFillColor(sf::Color::White);
    paintedFieldsText.setStyle(sf::Text::Bold);
    paintedFieldsText.setString("Score: " + std::to_string(paintedFields) + "%");
    paintedFieldsText.setPosition(18.f, 6.f);
    m_window.draw(paintedFieldsText);



    //obrot enemies
    m_enemy.rotate(5);

    //rysowanie enemies
    for (const auto& enemy : m_enemies)
    {
        m_enemy.setPosition(enemy.x, enemy.y);
        m_window.draw(m_enemy);
    }

    //przegrana gracza
    if (!m_player.alive)
    {
        m_window.draw(m_gameOver);
        m_gameoverSound.play();
    }

    //wygrana gracza
    if (m_player.win)
    {
        m_window.draw(m_win);
        m_winningSound.play();
        m_player.alive = 0;
    }

    m_window.display();
}



int Game::calculatePaintedFields()
{
    float paintedCount = -27;
    float totalCount = ((WIDTH_SIZE - 2) * (HEIGHT_SIZE - 2)) - 27;   // Pomijamy obramowanie i miejsce na procenty

    // Iteracja przez plansze i zliczanie komórek o wartosci 1 (zamalowanych pól)
    for (int i = 1; i < HEIGHT_SIZE - 1; ++i) // Pomijamy obramowanie
    {
        for (int j = 1; j < WIDTH_SIZE - 1; ++j)
        {
            if (m_board.grid[i][j] == 1)
            {
                ++paintedCount;
            }
        }
    }
    float result = paintedCount / totalCount;
    int score = static_cast<int>(result * 100); // Zamiana na procenty

    if (score >= 80)
    {
        m_player.win = true;
    }
    return score;
}


//mechanika kolizji garcza z bombami
void Game::checkPlayerBonusCollision(Player& player)
{
    sf::FloatRect playerBounds = m_tile.getGlobalBounds();//pobieranie granic dla gracza i zwracanie prostostokata ktory zajmuje

    for (auto it = m_bonuses.begin(); it != m_bonuses.end(); )
    {
        // Pobieranie globalnych granic bonusa i zwracanie obszzaru ktory zajmuje
        m_bonus.setPosition(it->getX() * 18, it->getY() * 18);
        sf::FloatRect bonusBounds = m_bonus.getGlobalBounds();

        // Sprawdz, czy gracz przecina sie z bonusem
        if (playerBounds.intersects(bonusBounds))       //sprawdzenie czy playerBounds i bonusBounds sie przecinaja
        {

            // Dzialania po kolizji
            m_board.reset();
            m_player = Player();
            m_gameoverSound.play();
            for (auto it = m_bonuses.begin(); it != m_bonuses.end(); )      //usuwanie wszystkich bomb
            {
                it = m_bonuses.erase(it);
            }
        }
        else
        {
            ++it; // Przechodzenie do nastepnego bonusa
        }
    }
}


//mechanika kolizji gracza z portalami
void Game::checkPlayerTeleportCollision(Player& player, Teleport& teleport1, Teleport& teleport2)
{
    static bool isTeleported = false;
    bool isInPortal1 = player.x == teleport1.m_x && player.y == teleport1.m_y;
    bool isInPortal2 = player.x == teleport2.m_x && player.y == teleport2.m_y;
    if (!isTeleported && isInPortal1)
    {
        isTeleported = true;
        player.x = teleport2.m_x;
        player.y = teleport2.m_y;
        m_teleportSound.play();
    }
    else if (!isTeleported && isInPortal2)
    {
        isTeleported = true;
        player.x = teleport1.m_x;
        player.y = teleport1.m_y;
        m_teleportSound.play();
    }
    else if (isTeleported && !(isInPortal1 || isInPortal2))
    {
        isTeleported = false;
    }
}



