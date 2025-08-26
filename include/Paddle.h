/**
 * @file Paddle.h
 * @brief This file defines the Paddle class for the game paddles.
 */
#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "Constants.h"

/**
 * @class Paddle
 * @brief Represents a paddle in the game.
 *
 * This class handles the movement and rendering of a paddle.
 */
class Paddle{
    public:
        /**
         * @brief Constructs a new Paddle object.
         * @param pos The initial position of the paddle.
         * @param vel The initial velocity of the paddle.
         */
        Paddle(sf::Vector2f pos, sf::Vector2f vel);
        /**
         * @brief Draws the paddle on the window.
         * @param window The SFML render window to draw on.
         */
        void Draw(sf::RenderWindow &window) {window.draw(m_rect);}
        /**
         * @brief Sets the vertical velocity of the paddle.
         * @param speed The new vertical speed.
         */
        void SetVy(float speed){m_velocity.y = speed;}
        /**
         * @brief Gets the horizontal velocity of the paddle.
         * @return The horizontal velocity.
         */
        float GetVx() const{return m_velocity.x;}
        /**
         * @brief Gets the vertical velocity of the paddle.
         * @return The vertical velocity.
         */
        float GetVy() const{return m_velocity.y;}
        /**
         * @brief Updates the paddle's position based on its velocity and delta time.
         * @param dt The delta time (time elapsed since the last frame).
         */
        void Update(float dt);
        /**
         * @brief Gets the current position of the paddle.
         * @return The position as a SFML Vector2f.
         */
        sf::Vector2f GetPosition() const{return m_rect.getPosition();}
        
    private:
        sf::Vector2f m_position;        ///< The position of the paddle.
        sf::Vector2f m_velocity;        ///< The velocity of the paddle.
        sf::RectangleShape m_rect;      ///< The SFML rectangle shape used for rendering the paddle.
};