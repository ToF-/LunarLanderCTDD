#include <stdio.h>
#include "allegro5/allegro5.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#define FONT_NAME "Dosis Light 300.ttf"

int main(int argc, char *argv[])
{
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
    ALLEGRO_TIMER * timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE * queue = al_create_event_queue();
    ALLEGRO_DISPLAY * display = al_create_display(display_size, display_size);

    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "../resources");
    al_change_directory(al_path_cstr(path, '/'));
    ALLEGRO_FONT * font = al_load_ttf_font(FONT_NAME, 32, 32);
    if(!font) {
        printf("unable to load ttf font:%s (path=%s)\n",FONT_NAME, al_path_cstr(path,'/'));
        return 1;
    }
    al_destroy_path(path);
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool redraw = true;
    ALLEGRO_EVENT event;
    
    al_start_timer(timer);
    while(true)
    {
        al_wait_for_event(queue, &event);
        if(event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        if(redraw && al_event_queue_is_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(0, 255, 0), 0, 0, 0, "Hello world!");
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
