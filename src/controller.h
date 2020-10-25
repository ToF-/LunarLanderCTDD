#define MAX_MESSAGE 80

typedef struct point {
    double x;
    double y;
} POINT;

typedef struct controller {
    bool active;
    char message[MAX_MESSAGE];
    POINT position;
    unsigned char keycode;
} CONTROLLER;

CONTROLLER * controller_create();
void controller_activate(CONTROLLER *controller);
void controller_tick(CONTROLLER *controller, unsigned long ticks);
void controller_command(CONTROLLER *controller, unsigned char key);
POINT controller_position(CONTROLLER *controller);
void controller_message(CONTROLLER *controller, char *message);
void controller_destroy(CONTROLLER *controller);


