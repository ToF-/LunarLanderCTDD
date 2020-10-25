typedef struct point {
    double x;
    double y;
} POINT;

typedef struct controller {
    char message[80];
    POINT position;
} CONTROLLER;

void controller_set_message(CONTROLLER * controller, char *message);
char *controller_get_message(CONTROLLER *controller);
void controller_set_position(CONTROLLER *controller, POINT position);
POINT controller_get_position(CONTROLLER *controller);
void controller_set_key(CONTROLLER *controller, char key);
char controller_get_key(CONTROLLER *controller);


