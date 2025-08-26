#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <string>

class Score
{
    public:
        Score(float position);
        void Draw(sf::RenderWindow &window){window.draw(m_text);};
        void Increase();
        int GetScore() {return m_score;}

    private:
        int m_score;
        float m_position;
        sf::Font m_font;
        sf::Text m_text;

};