#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) : m_selectedItemIndex(0)
{
    if (!m_font.loadFromFile("font/agency_fb.ttf"))
    {
        std::cerr << "Error loading font: font/agency_fb.ttf\n";
    }

    if (!m_backgroundTexture.loadFromFile("images/background.png"))
    {
        std::cerr << "Error loading texture: images/background.png\n";
    }
    m_backgroundSprite.setTexture(m_backgroundTexture);

    m_menu[0].setFont(m_font);
    m_menu[0].setFillColor(sf::Color::Red);
    m_menu[0].setString("Play");
    m_menu[0].setCharacterSize(60);
    m_menu[0].setPosition(width / 2.0f - 45.0f, height / 2.0f - 40.0f);

    m_menu[1].setFont(m_font);
    m_menu[1].setFillColor(sf::Color::White);
    m_menu[1].setString("High Scores");
    m_menu[1].setCharacterSize(60);
    m_menu[1].setPosition(width / 2.0f - 110.0f, height / 2.0f + 50.0f);

    m_menu[2].setFont(m_font);
    m_menu[2].setFillColor(sf::Color::White);
    m_menu[2].setString("Exit");
    m_menu[2].setCharacterSize(60);
    m_menu[2].setPosition(width / 2.0f - 35.0f, height / 2.0f + 140.0f);
}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(m_backgroundSprite);
    for (int i = 0; i < MAX_ITEMS; ++i)
    {
        window.draw(m_menu[i]);
    }
}

void Menu::moveUp()
{
    if (m_selectedItemIndex > 0)
    {
        m_menu[m_selectedItemIndex].setFillColor(sf::Color::White);
        m_selectedItemIndex--;
        m_menu[m_selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown()
{
    if (m_selectedItemIndex + 1 < MAX_ITEMS)
    {
        m_menu[m_selectedItemIndex].setFillColor(sf::Color::White);
        m_selectedItemIndex++;
        m_menu[m_selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

Menu::MenuOption Menu::getSelectedItem() const
{
    return static_cast<MenuOption>(m_selectedItemIndex);
}