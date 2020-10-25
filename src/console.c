#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_ttf.h"
#include "controller.h"


int main() {
    al_init();
    al_install_keyboard();

    ALLEGRO_TIMER * timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE * queue = al_create_event_queue();
    ALLEGRO_DISPLAY * display = al_create_display(640, 400);
    /* ALLEGRO_FONT * font = al_create_builtin_font(); */
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));
    al_destroy_path(path);
    ALLEGRO_FONT * font = al_load_ttf_font("courier.ttf", 48, 48);
    if(!font) {
        printf("unable to load ttf font:courier.ttf\n");
        return 1;
    }
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));


    bool redraw = true;
    ALLEGRO_EVENT event;

    CONTROLLER *controller = controller_create();
    controller_activate(controller);
    controller->position.x = 100;
    controller->position.y = 100;
    al_start_timer(timer);
    unsigned long ticks = 0;
    while(true)
    {
        al_wait_for_event(queue, &event);
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            ticks++;
            if(controller->active)
                controller_tick(controller,ticks);
            redraw = true;
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(controller->active)
                controller->keycode = event.keyboard.keycode;
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0x00, 0x00, 0x00));
            if(controller->active)
            {
                al_draw_text(font, al_map_rgb(0xff, 0xff, 0xff), 0x00, 0x00, 0x00, controller->message);
                double x = controller->position.x;
                double y = controller->position.y;
                al_draw_rectangle(x, y, x+20, y+20, al_map_rgb(0x00, 0xff, 0x80),3);
            }
            else 
                al_draw_text(font, al_map_rgb(0xff, 0xff, 0xff), 0x00, 0x00, 0x00, "Hello, world!");
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
