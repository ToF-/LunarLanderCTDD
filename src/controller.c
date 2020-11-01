#include "console.h"
#include "controller.h"
#include "trajectory.h"
#include <stdio.h>

static char state_message[80];
static LANDER lander;

void controller_init()
{
    lander_initialize(&lander);
    console_display("LUNAR LANDING -- READY");
}

void display_lander_state()
{
    sprintf(state_message, "HEIGHT:%06.1f -- VELOCITY:%05.1f -- FUEL:%04.1f",
            lander.height, lander.velocity, lander.fuel);
    console_display(state_message);
}
void controller_update(unsigned long ticks, float t, float r)
{
    if(ticks>=90)
    {
        lander_update(&lander, t, r);
        display_lander_state();
    }
}

float controller_last_relative_position()
{
    return (INITIAL_HEIGHT-lander.height) / INITIAL_HEIGHT;
}
