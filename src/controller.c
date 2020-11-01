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
void controller_tick(unsigned long ticks)
{
    if(ticks>=90)
        display_lander_state();
}

