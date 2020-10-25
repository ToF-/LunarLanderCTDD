#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_ttf.h"
#include "controller.h"


int main() {
    al_init();
    al_install_keyboard();

    ALLEGRO_TIMER * timer       = al_create_timer(1.0);
    ALLEGRO_EVENT_QUEUE * queue = al_create_event_queue();
    ALLEGRO_DISPLAY * display   = al_create_display(1024, 1024);

    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));
    ALLEGRO_FONT * font = al_load_ttf_font("courier.ttf", 24, 24);
    if(!font) {
        printf("unable to load ttf font:courier.ttf (path=%s)\n",al_path_cstr(path,'/'));
        return 1;
    }
    al_destroy_path(path);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));


    bool redraw = true;
    ALLEGRO_EVENT event;

    CONTROLLER *controller = controller_create();
    controller_activate(controller);
    al_start_timer(timer);
    unsigned long ticks = 0;
    while(true)
    {
        al_wait_for_event(queue, &event);
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            ticks++;
            controller_tick(controller,ticks);
            redraw = true;
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                break;
            controller->keycode = event.keyboard.keycode;
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0x00, 0x00, 0x00));
            al_draw_text(font, al_map_rgb(0xff, 0xff, 0xff), 0x00, 0x00, 0x00, controller->message);
            double x = controller->position.x;
            double y = controller->position.y;
            al_draw_rectangle(x, y, x+8, y+8, al_map_rgb(0x00, 0xff, 0x80),5);
            al_flip_display();
            redraw = false;
        }
    }
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    free(controller);
    return 0;
}
