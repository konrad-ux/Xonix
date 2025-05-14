#pragma once

class Teleport {
public:
    int m_x, m_y;

public:
    Teleport(int x, int y);

    int getX() const { return m_x; }
    int getY() const { return m_y; }

    void setPosition(int x, int y);
};
