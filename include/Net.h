/**
 * @file Net.h
 * @brief This file defines the Net class for drawing the center line and goal lines.
 */
#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"

/**
 * @class Net
 * @brief Represents a net or line in the game, used for the center line and goals.
 */
class Net
{
    public:
        /**
         * @brief Constructs a new Net object.
         * @param x The x-coordinate of the net.
         */
        Net(int x): m_x(x){};
        /**
         * @brief Draws the net on the window.
         * @param window The SFML render window to draw on.
         */
        void Draw(sf::RenderWindow &window);

    private:
        int m_x; ///< The x-coordinate of the net.
};