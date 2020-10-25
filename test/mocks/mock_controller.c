#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "controller.h"


CONTROLLER * controller_create() {
    return (CONTROLLER *)malloc(sizeof(CONTROLLER));
}
void controller_activate(CONTROLLER *controller) {
    controller->active = true;
    strcpy(controller->message,"MOCK CONTROLLER READY");
}
void controller_tick(CONTROLLER *controller, unsigned long ticks) {
    char buffer[80];
    sprintf(buffer,"TICKS:%ld", ticks);
    strcpy(controller->message, buffer);
}
void controller_destroy(CONTROLLER *controller) {
    free(controller);
}
