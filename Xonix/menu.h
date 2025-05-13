#pragma once
#include <SFML/Graphics.hpp>
#include <iostream> 

class Menu
{
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[2];
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

public:
    Menu(float width, float height);

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex() const;
};
