#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include "SpaceObject.h"

class Asteroid: public SpaceObject
{
private:
    int m_health;
    int m_color;
    int m_size;

public:
    Asteroid(int x, int y, float speed, int angle, int health, int size, int color);
    bool hit(void);
    int get_size(void)
    {
        return m_size;
    }
    int get_color(void)
    {
        return m_color;
    }
};

#endif // ASTEROID_H_INCLUDED
