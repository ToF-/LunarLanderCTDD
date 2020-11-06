#include "console.h"
#include "controller.h"
#include "trajectory.h"
#include <stdio.h>

static char state_message[80];
static LANDER lander;

void controller_init()
{
    lander_initialize(&lander);
    sprintf(state_message,"LUNAR LANDING -- READY IN 3");
    console_display(state_message);
}

void display_lander_state()
{
    switch(lander_status(lander))
    {
        case IN_FLIGHT:
        case NO_FUEL:
        {
            sprintf(state_message, "HEIGHT:%06.1f -- VELOCITY:%05.1f -- FUEL:%04.1f",
                    lander.height, lander.velocity, lander.fuel);
            break;
        }
        case LANDED:
        {
            sprintf(state_message, "STATUS:LANDED");
            break;
        }
        case CRASHED:
        {
            sprintf(state_message, "STATUS:CRASHED");
            break;
        }
    }
    console_display(state_message);
}
void controller_update(unsigned long ticks, float t, float r)
{
    if(ticks>=90)
    {
        lander_update(&lander, t, r);
        display_lander_state();
    }
    else
    {
        sprintf(state_message,"LUNAR LANDING -- READY IN %d", 3-((int)ticks)/30);
        console_display(state_message);
    }
}

float controller_last_relative_position()
{
    return (INITIAL_HEIGHT-lander.height) / INITIAL_HEIGHT;
}

int controller_lander_status()
{
    return lander_status(lander);
}
