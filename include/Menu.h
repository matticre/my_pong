#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <vector>

class Menu
{
    public:
        Menu();
        void Draw(sf::RenderWindow &window);
        void MoveUp();
        void MoveDown();
        void Select(sf::Event &event, bool &runMenu, bool &runGame);

    private:
        sf::Font m_font;
        std::vector<sf::Text> m_menu_text;
        int m_selected;
};