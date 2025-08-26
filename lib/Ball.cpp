#include "../include/Ball.h"

Ball::Ball(sf::Vector2f pos, sf::Vector2f vel): m_position(pos), m_velocity(vel)
{
    m_rect.setPosition(pos);
    m_rect.setSize(sf::Vector2f(BALL_WIDTH, BALL_HEIGHT));
}

void Ball::Update(const float &dt)
{
    m_rect.setPosition(m_rect.getPosition() + dt * m_velocity);
}

void Ball::CollideWithPaddle(Contact &contact)
{
    m_velocity.x = - m_velocity.x;

    if (contact.type == CollisionType::Top)
    {
        m_velocity.y = -0.75 * BALL_SPEED;
    }
    else if (contact.type == CollisionType::Bot)
    {
        m_velocity.y = 0.75 * BALL_SPEED;
    }
}

void Ball::CollideWithWall(const Contact &contact )
{
    m_velocity.y = - m_velocity.y;
    m_rect.setPosition(m_rect.getPosition().x, m_rect.getPosition().y + contact.penetration);

    if(contact.type == CollisionType::Left)
    {
        m_rect.setPosition(WINDOW_WIDTH / 2 - BALL_WIDTH / 2, WINDOW_HEIGHT / 2 - BALL_HEIGHT / 2);
        m_velocity.x = 0.0f;
        m_velocity.y = 0.0f;
    }
    else if(contact.type == CollisionType::Right)
    {
        m_rect.setPosition(WINDOW_WIDTH / 2 - BALL_WIDTH / 2, WINDOW_HEIGHT / 2 - BALL_HEIGHT / 2);
        m_velocity.x = 0.0f;
        m_velocity.y = 0.0f;
    }
}