#ifndef SHIP_CPP_INCLUDED
#define SHIP_CPP_INCLUDED

#include "SpaceObject.h"

class Ship: public SpaceObject
{

public:
    Ship(int x, int y);
    void left(void);
    void right(void);
};

#endif // SHIP_CPP_INCLUDED
