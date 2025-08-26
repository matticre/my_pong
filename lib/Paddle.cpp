#include "../include/Paddle.h"

Paddle::Paddle(sf::Vector2f pos, sf::Vector2f vel): m_position(pos), m_velocity(vel){
    m_rect.setPosition(pos);
    m_rect.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
}

void Paddle::Update(float dt){
    m_rect.setPosition(m_rect.getPosition() + dt * m_velocity );

    if (m_rect.getPosition().y < 0)
        m_rect.setPosition(m_rect.getPosition().x, 0);
        
    else if (m_rect.getPosition().y > (WINDOW_HEIGHT - PADDLE_HEIGHT))
        m_rect.setPosition(m_rect.getPosition().x, WINDOW_HEIGHT - PADDLE_HEIGHT);
}