#ifndef PADDLE
#define PADDLE

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Paddle
{
    public:
        Paddle(sf::Vector2f pos, sf::Vector2f vel): m_position(pos), m_velocity(vel) 
        {
            m_rect.setPosition(pos);
            m_rect.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
        } 

        void Draw(sf::RenderWindow &window) {window.draw(m_rect);}

    private:
        sf::Vector2f m_position;
        sf::Vector2f m_velocity;
        sf::RectangleShape m_rect;
};

#endif