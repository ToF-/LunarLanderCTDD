#include <stdio.h>
#include "allegro5/allegro5.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"
#include "trajectory.h"
#include "console.h"
#include "controller.h"
#define FONT_NAME "courier.ttf"
#define REDRAW_RATE (1.0 / 30.0)

float Redraw_Rate = REDRAW_RATE;
int Display_Size = 1200;
char message[80];
void console_display(char *s)
{
    sprintf(message, "%s", s);

}

int console_init(ALLEGRO_FONT **font, ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer, ALLEGRO_EVENT_QUEUE **queue)
{
    al_init();
    al_install_keyboard();
    *timer = al_create_timer(Redraw_Rate);
    *queue = al_create_event_queue();
    *display = al_create_display(Display_Size, Display_Size);

    al_init_ttf_addon();
    al_init_font_addon();
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "../resources");
    al_change_directory(al_path_cstr(path, '/'));
    *font = al_load_ttf_font(FONT_NAME, 24, 24);
    if(!font) {
        printf("unable to load ttf font:%s (path=%s)\n",FONT_NAME, al_path_cstr(path,'/'));
        return 1;
    }
    al_destroy_path(path);
    al_register_event_source(*queue, al_get_keyboard_event_source());
    al_register_event_source(*queue, al_get_display_event_source(*display));
    al_register_event_source(*queue, al_get_timer_event_source(*timer));
    return 0;
}
void console_redraw(ALLEGRO_DISPLAY *display, float burn_rate, ALLEGRO_FONT *font)
{
    float x,y;
    ALLEGRO_COLOR display_color = al_map_rgb(0, 255, 0);
    
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font, display_color, 10, 10, 0, message);
    al_draw_line(0.0, (float)al_get_display_height(display)-20.0, (float)al_get_display_width(display), (float)al_get_display_height(display)-20.0, al_map_rgb(0,255,5),1.0);
    x = (float)al_get_display_width(display)/2;
    y = controller_last_relative_position() * ((float)al_get_display_height(display)-30.0);
    al_draw_filled_rectangle(x, y, x + 10, y + 10, al_map_rgb(255, 255, 255));
    if(burn_rate > 0.0)
        if(controller_lander_status() == IN_FLIGHT)
        {
            al_draw_filled_triangle(x+5, y+10, x, y+15, x+10, y+15, al_map_rgb(255, 255, 0));
            al_draw_filled_triangle(x, y+15, x+10, y+15, x+5, y+25, al_map_rgb(255, 255, 0));
        }

    al_flip_display();
}
void console_exit(ALLEGRO_FONT *font, ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer, ALLEGRO_EVENT_QUEUE *queue)
{
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}

void console_loop(ALLEGRO_FONT *font, ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer, ALLEGRO_EVENT_QUEUE *queue)
{
    ALLEGRO_EVENT event;
    bool quit = false;
    bool redraw = true;
    bool key_down = false;
    unsigned char key_code;
    unsigned long ticks=0;
    float burn_rate = 0.0;
    float x,y;
    x = (float)al_get_display_width(display)/2;
    y = (float)al_get_display_height(display)/5;
    al_start_timer(timer);
    while(!quit)
    {
        al_wait_for_event(queue, &event);
        switch(event.type) 
        {
            case ALLEGRO_EVENT_TIMER:
            {
                controller_update(ticks, Redraw_Rate, burn_rate);
                ticks++;
                redraw = true;
                break;
            }
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
            {
                quit = true;
                break;
            }
            case ALLEGRO_EVENT_KEY_DOWN:
            {
                key_code = event.keyboard.keycode;
                if(key_code == ALLEGRO_KEY_SPACE)
                    burn_rate = 1.0;
                else if(key_code == ALLEGRO_KEY_ESCAPE)
                    quit = true;
                break;
            }
            case ALLEGRO_EVENT_KEY_UP:
            {

                key_down = false;
                burn_rate = 0.0;
            }
            break;
        }
        if(redraw && al_event_queue_is_empty(queue))
        {
            console_redraw(display, burn_rate, font);
            redraw = false;
        }
    }
}
int main(int argc, char *argv[])
{
    ALLEGRO_FONT *font;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_DISPLAY *display;
    if(argc > 1)
    {
        int size;
        sscanf(argv[1], "%d", &size);
        if(size >= 200 && size <= 1200)
            Display_Size = size;
    }
    int exit_code = console_init(&font, &display, &timer, &queue);
    if(exit_code)
        return exit_code;

    controller_init();
    console_loop(font, display, timer, queue);
    console_exit(font, display, timer, queue);

    return 0;
}
