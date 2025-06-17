#include "menu.h"

Menu::Menu(float width, float height)
    : selectedItemIndex(0)
{
    if (!font.loadFromFile("font/agency_fb.ttf"))
        std::cerr << "B³¹d ³adowania czcionki agency_fb.ttf\n";

    if (!backgroundTexture.loadFromFile("images/background.png"))
        std::cerr << "B³¹d ³adowania t³a menu2.png\n";
    backgroundSprite.setTexture(backgroundTexture);

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play");
    menu[0].setCharacterSize(60);
    menu[0].setPosition(width / 2 - 45, height / 2 - 40);

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("High Scores");
    menu[1].setCharacterSize(60);
    menu[1].setPosition(width / 2 - 110, height / 2 + 50);

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Exit");
    menu[2].setCharacterSize(60);
    menu[2].setPosition(width / 2 - 35, height / 2 + 140);
}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(backgroundSprite);
    for (int i = 0; i < MAX_ITEMS; ++i)
        window.draw(menu[i]);
}

void Menu::moveUp()
{
    if (selectedItemIndex > 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown()
{
    if (selectedItemIndex + 1 < MAX_ITEMS) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

// POPRAWKA: Definicja brakuj¹cej funkcji
Menu::MenuOption Menu::getSelectedItem() const
{
    return static_cast<MenuOption>(selectedItemIndex);
}