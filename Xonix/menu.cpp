#include "menu.h"

Menu::Menu(float width, float height)
    : selectedItemIndex(0)
{
    if (!font.loadFromFile("font/agency_fb.ttf"))
        std::cerr << "B³¹d ³adowania czcionki agency_fb.ttf\n";

    if (!backgroundTexture.loadFromFile("images/menu2.png"))
        std::cerr << "B³¹d ³adowania t³a menu2.png\n";
    backgroundSprite.setTexture(backgroundTexture);

    // 0: Start
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Start");
    menu[0].setCharacterSize(40);
    menu[0].setPosition(width / 2 - 50, height / 2 - 80);

    // 1: Tablica wyników
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Tablica wyników");
    menu[1].setCharacterSize(40);
    menu[1].setPosition(width / 2 - 100, height / 2 - 20);

    // 2: Exit
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Exit");
    menu[2].setCharacterSize(40);
    menu[2].setPosition(width / 2 - 50, height / 2 + 40);
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

int Menu::getSelectedItemIndex() const
{
    return selectedItemIndex;
}
