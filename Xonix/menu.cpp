#include "menu.h"

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("agency_fb.ttf"))
    {
        std::cerr << "B³¹d ³adowania czcionki agency_fb.ttf" << std::endl;
    }

    if (!backgroundTexture.loadFromFile("menu2.png"))
    {
        std::cerr << "B³¹d ³adowania t³a menu.png" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Start");
    menu[0].setCharacterSize(40);
    menu[0].setPosition(sf::Vector2f(width / 2.f - 50, height / 2.f - 40));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Exit");
    menu[1].setCharacterSize(40);
    menu[1].setPosition(sf::Vector2f(width / 2.f - 50, height / 2.f + 20));



    selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(backgroundSprite);  // Rysuj najpierw t³o

    for (int i = 0; i < 2; ++i)
    {
        window.draw(menu[i]);
    }
}

void Menu::moveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown()
{
    if (selectedItemIndex + 1 < 2)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

int Menu::getSelectedItemIndex() const
{
    return selectedItemIndex;
}
