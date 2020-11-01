#include "trajectory.h"

void lander_initialize(LANDER *lander)
{
    lander->height = INITIAL_HEIGHT;
    lander->velocity = INITIAL_VELOCITY;
    lander->fuel = INITIAL_FUEL;
}
