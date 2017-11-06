#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "SpaceObject.h"

class Bullet: public SpaceObject
{
public:
    Bullet(int x, int y, int angle, sf::Texture &t);
    bool is_alive(void)
    {
        if(m_frame_cnt < 30)
            return true;

        return false;
    }
};


#endif // BULLET_H_INCLUDED
