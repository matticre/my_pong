#include "../include/Score.h"

Score::Score (float position):m_position(position)
{
    m_score = 0;
    m_font.loadFromFile("/home/mattia/github/my_pong/media/DejaVuSansMono.ttf");
    m_text.setFont(m_font);
    m_text.setString(std::to_string((m_score)));
    m_text.setCharacterSize(35);
    m_text.setPosition(m_position, 50.0f);
}

void Score::Increase()
{
    ++m_score;
    m_text.setString(std::to_string(m_score));
}