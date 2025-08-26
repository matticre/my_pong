#pragma once

#include "Constants.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

enum class CollisionType
{
    None,
    Top,
    Middle,
    Bot,
    Left,
    Right
};

struct Contact
{
    CollisionType type;
    float penetration;
};

class Ball
{
    public:
        Ball(sf::Vector2f pos, sf::Vector2f vel);
        void Update(const float &dt);
        void Draw(sf::RenderWindow &window) {window.draw(m_rect);}
        sf::Vector2f GetPosition() const{return m_rect.getPosition();}
        sf::Vector2f GetVelocity() const{return m_velocity;}
        void SetVx(float speed){m_velocity.x = speed;}
        void SetVy(float speed){m_velocity.y = speed;}
        float GetVx() const {return m_velocity.x;}
        float GetVy() const{return m_velocity.y;}
        void CollideWithPaddle(Contact &contact);
        void CollideWithWall(const Contact &contact);


    private:
        sf::Vector2f m_position;
        sf::Vector2f m_velocity;
        sf::RectangleShape m_rect;
};