#include <assert.h>
#include "allegro5/allegro5.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"
#include "console.h"
#include "controller.h"

#define FONT_NAME "courier.ttf"
#define REDRAW_RATE (1.0 / 30.0)

int Display_Size = 1200;
float X_Lander, Y_Lander;
float Redraw_Rate = REDRAW_RATE;

ALLEGRO_TIMER *Timer;
ALLEGRO_EVENT_QUEUE *Queue;
ALLEGRO_DISPLAY *Display;
ALLEGRO_FONT *Font;

ALLEGRO_COLOR Green;
ALLEGRO_COLOR Orange;
ALLEGRO_COLOR Display_Color;

int console_init()
{
    al_init();
    al_install_keyboard();
    Timer = al_create_timer(Redraw_Rate);
    Queue = al_create_event_queue();
    Display = al_create_display(Display_Size, Display_Size);
    Green  = al_map_rgb(0, 255, 0);
    Orange = al_map_rgb(255,127, 0);
    Display_Color = Green;
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "../resources");
    al_change_directory(al_path_cstr(path, '/'));
    Font = al_load_ttf_font(FONT_NAME, 24, 24);
    if(!Font) {
        printf("unable to load ttf font:%s (path=%s)\n",FONT_NAME, al_path_cstr(path,'/'));
        return 1;
    }
    al_register_event_source(Queue, al_get_keyboard_event_source());
    al_register_event_source(Queue, al_get_display_event_source(Display));
    al_register_event_source(Queue, al_get_timer_event_source(Timer));
    return 0;
}
void console_destroy()
{
    al_destroy_font(Font);
    al_destroy_display(Display);
    al_destroy_timer(Timer);
    al_destroy_event_queue(Queue);
}

void console_display(char *s)
{
    sprintf(Console_Message, "%s", s);
}

void console_redraw()
{
    assert(false);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(Font, Display_Color, 10, 10, 0, Console_Message);
    al_draw_line(0.0, (float)(Display_Size-30.0), (float)Display_Size, (float)(Display_Size-30.0), al_map_rgb(0,255,5),1.0);
    al_draw_filled_rectangle(X_Lander, Y_Lander, X_Lander + 10, Y_Lander + 10, al_map_rgb(255, 0, 0));
    al_flip_display();
}

int game_loop(int argc, char *argv[])
{
    float burn_rate = 0.0;
    if(argc > 1)
    {
        int size;
        printf("adjusting size...");
        sscanf(argv[1], "%d", &size);
        printf("to %d\n", size);
        if(size >= 200 && size <= 1200)
            Display_Size = size;
    }
    int exit_code = al_init();
    if (exit_code != 0)
        return exit_code;

    bool quit = false;;
    bool redraw = true;
    bool key_down = false;
    unsigned char key_code;
    unsigned long ticks=0;
    X_Lander = (float)al_get_display_width(Display)/2;
    Y_Lander = (float)al_get_display_height(Display)/5;
    ALLEGRO_EVENT event;
    controller_init();
    al_start_timer(Timer);
    while(!quit)
    {
        al_wait_for_event(Queue, &event);
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            controller_update(ticks, Redraw_Rate, burn_rate);
            ticks++;
            Y_Lander = controller_last_relative_position() * ((float)al_get_display_height(Display)-30.0);
            redraw = true;
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            quit = true;
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            key_down = true;
            key_code = event.keyboard.keycode;
            Display_Color = Green;
            if(key_down)
            {
                if(key_code == ALLEGRO_KEY_SPACE)
                {   
                    burn_rate = 1.0;
                    Display_Color = Orange;
                }
                else if(key_code == ALLEGRO_KEY_ESCAPE)
                    quit = true;
            }
            else
            {
                Display_Color = Green;
            }
        }
        else if(event.type == ALLEGRO_EVENT_KEY_UP)
        {
            key_down = false;
            burn_rate = 0.0;
        }
        if(redraw && al_event_queue_is_empty(Queue))
        {
            console_redraw();
            redraw = false;
        }
    }
    return 0;
}
