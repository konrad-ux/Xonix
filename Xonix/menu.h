#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu
{
public:
    // ZMIANA: U¿ycie enum class dla opcji menu
    enum class MenuOption { Start, HighScores, Exit, Count };

    Menu(float width, float height);

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    MenuOption getSelectedItem() const; // Zwraca teraz typ enum

private:
    // ZMIANA: MAX_ITEMS jest teraz wyliczane na podstawie enuma
    static const int MAX_ITEMS = static_cast<int>(MenuOption::Count);

    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_ITEMS];
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};