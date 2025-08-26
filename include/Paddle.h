#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Paddle
{
    public:
        Paddle(sf::Vector2f pos, sf::Vector2f vel);
        void Draw(sf::RenderWindow &window) {window.draw(m_rect);}
        void SetVy(float speed){m_velocity.y = speed;}
        float GetVx() const{return m_velocity.x;}
        float GetVy() const{return m_velocity.y;}
        void Update(float dt);
        sf::Vector2f GetPosition() const{return m_rect.getPosition();}
        
    private:
        sf::Vector2f m_position;
        sf::Vector2f m_velocity;
        sf::RectangleShape m_rect;
};