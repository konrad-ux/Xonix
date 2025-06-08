#pragma once
#include "Bonus.h"

class Teleport: public Bonus {
public:
    int m_x, m_y;

public:
    Teleport(int x, int y);

    int getX() const { return m_x; }
    int getY() const { return m_y; }

    void setPosition(int x, int y);
};
