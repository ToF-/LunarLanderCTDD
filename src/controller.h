typedef struct point {
    double x;
    double y;
} POINT;

typedef struct controller {
    bool active;
    char message[80];
    POINT position;
    unsigned char keycode;
} CONTROLLER;

CONTROLLER * controller_create();
void controller_activate(CONTROLLER *controller);
void controller_tick(CONTROLLER *controller, unsigned long ticks);
void controller_destroy(CONTROLLER *controller);


