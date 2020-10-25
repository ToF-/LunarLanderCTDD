#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "controller.h"


CONTROLLER * controller_create() 
{
    return (CONTROLLER *)malloc(sizeof(CONTROLLER));
}

void controller_activate(CONTROLLER *controller) 
{
    controller->active = true;
    controller->position.x = 100; 
    controller->position.y = 100;
    strcpy(controller->message,"MOCK CONTROLLER READY");
}

void controller_tick(CONTROLLER *controller, unsigned long ticks)
{
    char buffer[80];
    controller->position.y += 5;
    sprintf(buffer,"HEIGHT:%02.1f", 1000-controller->position.y);
    strcpy(controller->message, buffer);
}
void controller_command(CONTROLLER *controller, unsigned char key)
{
}
void controller_message(CONTROLLER *controller, char *message)
{
    strncpy(message, controller->message, MAX_MESSAGE);
}
void controller_destroy(CONTROLLER *controller) {
    free(controller);
}
