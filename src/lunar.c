#include <stdio.h>
#include "allegro5/allegro5.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"
#include "console.h"
#include "controller.h"
#define FONT_NAME "Dosis Light 300.ttf"
#define REDRAW_RATE (1.0 / 30.0)

char message[80];
void console_display(char *s)
{
    sprintf(message, "%s", s);

}
int main(int argc, char *argv[])
{
    float redraw_rate = REDRAW_RATE;
    float burn_rate = 0.0;
    int display_size=1000;
    if(argc > 1)
    {
        int size;
        printf("adjusting size...");
        sscanf(argv[1], "%d", &size);
        printf("to %d\n", size);
        if(size >= 200 && size <= 1000)
            display_size = size;
    }
    al_init();
    al_install_keyboard();
    ALLEGRO_TIMER * timer = al_create_timer(redraw_rate);
    ALLEGRO_EVENT_QUEUE * queue = al_create_event_queue();
    ALLEGRO_DISPLAY * display = al_create_display(display_size, display_size);

    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "../resources");
    al_change_directory(al_path_cstr(path, '/'));
    ALLEGRO_FONT *font = al_load_ttf_font(FONT_NAME, 32, 32);
    if(!font) {
        printf("unable to load ttf font:%s (path=%s)\n",FONT_NAME, al_path_cstr(path,'/'));
        return 1;
    }
    al_destroy_path(path);
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool redraw = true;
    bool key_down = false;
    unsigned char key_code;
    unsigned long ticks=0;
    float x,y;
    x = (float)al_get_display_width(display)/2;
    y = (float)al_get_display_height(display)/5;
    ALLEGRO_EVENT event;
    ALLEGRO_COLOR green = al_map_rgb(0, 255, 0);
    ALLEGRO_COLOR orange = al_map_rgb(255,127, 0);
    ALLEGRO_COLOR display_color = green;
    
    controller_init();
    al_start_timer(timer);
    while(true)
    {
        al_wait_for_event(queue, &event);
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            controller_update(ticks, redraw_rate, burn_rate);
            ticks++;

            y = controller_last_relative_position() * ((float)al_get_display_height(display));
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            key_down = true;
            key_code = event.keyboard.keycode;
        }
        else if(event.type == ALLEGRO_EVENT_KEY_UP)
        {
            key_down = false;
            burn_rate = 0.0;
        }
        if(redraw && al_event_queue_is_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            if(key_down)
            {
                if(key_code == ALLEGRO_KEY_SPACE)
                {   
                    burn_rate = 1.0;
                    display_color = orange;
                }
                else
                    display_color = green;
            }
            else
            {
                display_color = green;
            }
            al_draw_text(font, display_color, 10, 10, 0, message);
            al_draw_filled_rectangle(x, y, x + 10, y + 10, al_map_rgb(255, 0, 0));

            al_flip_display();
            redraw = false;
        }
    }

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    return 0;
}
