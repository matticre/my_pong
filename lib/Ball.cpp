#include "../include/Ball.h"

Ball::Ball(sf::Vector2f pos, sf::Vector2f vel): m_position(pos), m_velocity(vel)
{
    m_rect.setPosition(pos);
    m_rect.setSize(sf::Vector2f(BALL_WIDTH, BALL_HEIGHT));
}