/**
 * @file Ball.h
 * @brief This file defines the Ball class and related collision structures.
 */
#pragma once

#include "Constants.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

/**
 * @enum CollisionType
 * @brief An enumeration to define the type of collision that occurred.
 */
enum class CollisionType
{
    None,
    Top,
    Middle,
    Bot,
    Left,
    Right
};

/**
 * @struct Contact
 * @brief A structure to hold information about a collision.
 */
struct Contact
{
    CollisionType type; ///< The type of collision.
    float penetration;  ///< The depth of penetration.
};

/**
 * @class Ball
 * @brief Represents the ball in the game, handling its movement and collisions.
 */
class Ball
{
    public:
        /**
         * @brief Constructs a new Ball object.
         * @param pos The initial position of the ball.
         * @param vel The initial velocity of the ball.
         */
        Ball(sf::Vector2f pos, sf::Vector2f vel);
        /**
         * @brief Updates the ball's position based on its velocity and delta time.
         * @param dt The delta time (time elapsed since the last frame).
         */
        void Update(const float &dt);
        /**
         * @brief Draws the ball on the window.
         * @param window The SFML render window to draw on.
         */
        void Draw(sf::RenderWindow &window) {window.draw(m_rect);}
        /**
         * @brief Gets the current position of the ball.
         * @return The position as a SFML Vector2f.
         */
        sf::Vector2f GetPosition() const{return m_rect.getPosition();}
        /**
         * @brief Gets the current velocity of the ball.
         * @return The velocity as a SFML Vector2f.
         */
        sf::Vector2f GetVelocity() const{return m_velocity;}
        /**
         * @brief Sets the horizontal velocity of the ball.
         * @param speed The new horizontal speed.
         */
        void SetVx(float speed){m_velocity.x = speed;}
        /**
         * @brief Sets the vertical velocity of the ball.
         * @param speed The new vertical speed.
         */
        void SetVy(float speed){m_velocity.y = speed;}
        /**
         * @brief Gets the horizontal velocity of the ball.
         * @return The horizontal velocity.
         */
        float GetVx() const {return m_velocity.x;}
        /**
         * @brief Gets the vertical velocity of the ball.
         * @return The vertical velocity.
         */
        float GetVy() const{return m_velocity.y;}
        /**
         * @brief Handles a collision with a paddle.
         * @param contact The contact information from the collision.
         */
        void CollideWithPaddle(Contact &contact);
        /**
         * @brief Handles a collision with a wall.
         * @param contact The contact information from the collision.
         */
        void CollideWithWall(const Contact &contact);


    private:
        sf::Vector2f m_position;        ///< The position of the ball.
        sf::Vector2f m_velocity;        ///< The velocity of the ball.
        sf::RectangleShape m_rect;      ///< The SFML rectangle shape used for rendering the ball.
};