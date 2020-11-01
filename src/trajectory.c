#include "trajectory.h"

void lander_initialize(LANDER *lander)
{
    lander->height = INITIAL_HEIGHT;
    lander->velocity = INITIAL_VELOCITY;
    lander->fuel = INITIAL_FUEL;
}

void lander_update(LANDER * lander, float t, float burn_rate)
{
    lander->height += t * lander->velocity;
    lander->velocity += t * (STRENGTH * burn_rate - GRAVITY);
}

