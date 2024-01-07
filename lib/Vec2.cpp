#include "../include/Vec2.h"

Vec2 Vec2::operator+ (Vec2 const &vec) 
{
    return Vec2(m_x + vec.m_x, m_y + vec.m_y);
};

Vec2& Vec2::operator+=(Vec2 const &vec)
{
    m_x += vec.m_x;
    m_y += vec.m_y;
    return *this;
};

Vec2 Vec2::operator* (const float &scalar) 
{
    return Vec2(m_x * scalar, m_y * scalar);
};