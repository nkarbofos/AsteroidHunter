#include "stdlib.h"
#include "utils.h"

float rnd(int m)
{
    return float(rand())/RAND_MAX*m;
}
