#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu
{
private:
    static const int MAX_ITEMS = 3;
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_ITEMS];
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

public:
    Menu(float width, float height);

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int  getSelectedItemIndex() const;
};
