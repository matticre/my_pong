/**
 * @file Score.h
 * @brief This file defines the Score class for displaying player scores.
 */
#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <string>

/**
 * @class Score
 * @brief Represents the score display for a player.
 */
class Score{
    public:
        /**
         * @brief Constructs a new Score object.
         * @param position The x-coordinate for the score display.
         */
        Score(float position);
        /**
         * @brief Draws the score on the window.
         * @param window The SFML render window to draw on.
         */
        void Draw(sf::RenderWindow &window){window.draw(m_text);};
        /**
         * @brief Increases the score by one.
         */
        void Increase();
        /**
         * @brief Gets the current score.
         * @return The current score as an integer.
         */
        int GetScore() {return m_score;}

    private:
        int m_score;            ///< The current score value.
        float m_position;       ///< The x-coordinate of the score display.
        sf::Font m_font;        ///< The font used for the score text.
        sf::Text m_text;        ///< The SFML text object for the score.

};