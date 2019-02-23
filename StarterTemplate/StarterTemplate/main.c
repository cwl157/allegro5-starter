#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

void init_component(bool initResult, const char *description)
{
	if (initResult) return;

	printf("couldn't initialize %s\n", description);
	exit(1);
}

int main()
{
	double FPS = 30.0;

	init_component(al_init(), "allegro");
	init_component(al_install_keyboard(), "keyboard");
	init_component(al_init_image_addon(), "images");
	init_component(al_init_primitives_addon(), "primitives");

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	init_component(timer, "timer");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	init_component(queue, "event queue");

	ALLEGRO_DISPLAY* disp = al_create_display(640, 480);
	init_component(disp, "display");

	ALLEGRO_FONT* font = al_create_builtin_font();
	init_component(font, "font");

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool done = false;
	bool redraw = true;
	ALLEGRO_EVENT event;

	al_start_timer(timer);
	while (1)
	{
		al_wait_for_event(queue, &event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			// game logic goes here.
			redraw = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;
		}

		if (done)
			break;

		if (redraw && al_is_event_queue_empty(queue))
		{
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");
			al_flip_display();

			redraw = false;
		}
	}

	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}