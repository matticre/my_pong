#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"

class Net
{
    public:
        Net(int x): m_x(x){};
        void Draw(sf::RenderWindow &window);
    
    private:
        int m_x;
};