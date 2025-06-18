#pragma once

#include <SFML/Graphics.hpp>

class Menu {
public:
    enum class MenuOption {
        Start,
        HighScores,
        Exit,
        Count
    };

    Menu(float width, float height);

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    MenuOption getSelectedItem() const;

private:
    static constexpr int MAX_ITEMS = static_cast<int>(MenuOption::Count);

    int m_selectedItemIndex;
    sf::Font m_font;
    sf::Text m_menu[MAX_ITEMS];
    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;
};