#include "../include/Score.h"
#include <iostream>

Score::Score (float position):m_position(position)
{
    m_score = 0;
    if(!m_font.loadFromFile("./media/DejaVuSansMono.ttf"))
    {
        std::cerr << "Error! Font not loaded." << std::endl; 
    }
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