#define STRENGTH 1.0
#define GRAVITY 0.5
#define INITIAL_HEIGHT 50.0
#define INITIAL_VELOCITY 0.0
#define INITIAL_FUEL 20.0
#define SAFE_VELOCITY (-0.5)
#define IN_FLIGHT 0
#define LANDED 1
#define CRASHED 2

typedef struct {
    float height;
    float velocity;
    float fuel;
} LANDER;

void lander_initialize(LANDER *);
void lander_update(LANDER *, float, float);
int lander_status(LANDER);
