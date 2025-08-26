/**
 * @file Menu.h
 * @brief This file defines the Menu class for the game's main menu.
 */
#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <vector>

/**
 * @class Menu
 * @brief Represents the main menu of the game, handling navigation and selection.
 */
class Menu
{
    public:
        /**
         * @brief Constructs a new Menu object.
         */
        Menu();
        /**
         * @brief Draws the menu on the window.
         * @param window The SFML render window to draw on.
         */
        void Draw(sf::RenderWindow &window);
        /**
         * @brief Moves the selection up in the menu.
         */
        void MoveUp();
        /**
         * @brief Moves the selection down in the menu.
         */
        void MoveDown();
        /**
         * @brief Handles the selection of a menu item.
         * @param event The SFML event to process.
         * @param runMenu A reference to the boolean controlling the menu loop.
         * @param runGame A reference to the boolean controlling the game loop.
         */
        void Select(sf::Event &event, bool &runMenu, bool &runGame);

    private:
        sf::Font m_font; ///< The font used for the menu text.
        std::vector<sf::Text> m_menu_text; ///< A vector of SFML Text objects for menu items.
        int m_selected; ///< The index of the currently selected menu item.
};