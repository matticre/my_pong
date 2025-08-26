#include "../include/Menu.h"
#include <iostream>

Menu::Menu()
{
    m_selected = 0;

    if (!m_font.loadFromFile("./media/DejaVuSansMono.ttf"))
    {
        std::cerr << "Error! Font not loaded." << std::endl; 
    }

    m_menu_text.resize(2);

    m_menu_text[0].setString("Play");
    m_menu_text[0].setFont(m_font);
    m_menu_text[0].setFillColor(sf::Color::Blue);
    m_menu_text[0].setPosition(WINDOW_WIDTH / 2 - m_menu_text[0].getLocalBounds().width, WINDOW_HEIGHT / 4);
    m_menu_text[0].setCharacterSize(60);

    m_menu_text[1].setString("Exit");
    m_menu_text[1].setFont(m_font);
    m_menu_text[1].setFillColor(sf::Color::White);
    m_menu_text[1].setPosition(WINDOW_WIDTH / 2 - m_menu_text[1].getLocalBounds().width, WINDOW_HEIGHT * 2 / 4);
    m_menu_text[1].setCharacterSize(60);
}

void Menu::Draw(sf::RenderWindow &window)
{
    window.draw(m_menu_text[0]);
    window.draw(m_menu_text[1]);
}

void Menu::MoveUp()
{
    if (m_selected >= 0)
    {
        m_menu_text[m_selected].setFillColor(sf::Color::White);
        --m_selected;
        
        if (m_selected < 0)
        {
            m_selected = 1;
        }

        m_menu_text[m_selected].setFillColor(sf::Color::Blue);
    }
}

void Menu::MoveDown()
{
    if (m_selected <= m_menu_text.size())
    {
        m_menu_text[m_selected].setFillColor(sf::Color::White);
        ++m_selected;
        
        if (m_selected >= 2)
        {
            m_selected = 0;
        }

        m_menu_text[m_selected].setFillColor(sf::Color::Blue);
    }
}

void Menu::Select(sf::Event &event, bool &runMenu, bool &runGame)
{ 
    if (event.key.code == sf::Keyboard::Enter)
    {
        std::cout << m_selected << std::endl;
        if (m_selected == 0)
        {
            runMenu = false;
        }
        else 
        {
            runMenu = false;
            runGame = false;
        }
    }
}
