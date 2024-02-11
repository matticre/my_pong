#ifndef BALL
#define BALL

#include "Constants.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class Ball
{
    public:
        Ball(sf::Vector2f pos, sf::Vector2f vel);

        void Draw(sf::RenderWindow &window) {window.draw(m_rect);}

    private:
        sf::Vector2f m_position;
        sf::Vector2f m_velocity;
        sf::RectangleShape m_rect;
};

#endif