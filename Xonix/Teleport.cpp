#include"Teleport.h"



Teleport::Teleport(int x, int y)
    : Bonus(x, y), m_x(x), m_y(y)
{
}




void Teleport::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}
