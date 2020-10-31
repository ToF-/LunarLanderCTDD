#include "console.h"
#include "controller.h"
#include <stdio.h>

void controller_init()
{
    console_display("LUNAR LANDING -- READY");
}

void controller_tick(unsigned long ticks)
{
    if(ticks>=90)
        console_display("HEIGHT:0050.0 -- VELOCITY:0.0 -- FUEL:00.0");
}

