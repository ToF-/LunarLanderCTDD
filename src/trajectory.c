#include "trajectory.h"

void lander_initialize(LANDER *lander)
{
    lander->height = INITIAL_HEIGHT;
    lander->velocity = INITIAL_VELOCITY;
    lander->fuel = INITIAL_FUEL;
}

void lander_update(LANDER * lander, float t, float burn_rate)
{
    if(lander_status(*lander)==IN_FLIGHT)
    {
        float actual_rate = lander->fuel >= t * burn_rate ? burn_rate : 0.0;
        lander->height += t * lander->velocity;
        lander->velocity += t * (STRENGTH * actual_rate - GRAVITY);
        lander->fuel -= t*actual_rate;
    }
}

int lander_status(LANDER lander)
{
    if(lander.height <= 0.0)
    {
        if(lander.velocity >= SAFE_VELOCITY)
            return LANDED;
        else
            return CRASHED;
    }
    return IN_FLIGHT;
}

