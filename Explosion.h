#ifndef EXPLOSION_INCLUDED
#define EXPLOSION_INCLUDED

#include "SpaceObject.h"

class Explosion: public SpaceObject
{
private:
    int cut_x, cut_y, cut_cnt;
public:
    bool is_alive(void);
    Explosion(int x, int y);
    void update(void);
};

#endif // EXPLOSION_INCLUDED
