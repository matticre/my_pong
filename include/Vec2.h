#ifndef VEC2 
#define VEC2 

class Vec2
{
    private:
        float m_x;
        float m_y;
    public:
        Vec2( float x, float y): m_x(x), m_y(y){};
        //Getters
        float GetX() const {return m_x;};
        float GetY() const {return m_y;};
        //Setters
        void  SetX(const float &x) {m_x = x;};   
        void  SetY(const float &y) {m_y = y;};

        Vec2  operator+(Vec2 const &vec);
        Vec2& operator+=(Vec2 const &vec); 
        Vec2  operator* (const float &scalar);
};

#endif