#include "./allegro.h"

/**
 * Allocate memory for Allegro config structure.
 */
Allegro *allegro_create() {
	Allegro *allegro = malloc(sizeof(Allegro));

	if (!allegro) {
		return NULL;
	}

	allegro->display = NULL;
	allegro->event_queue = NULL;
	allegro->timer = NULL;
	allegro->font = NULL;

	return allegro;
}

/**
 * Initialize Allegro config structure by creating and registering the
 * display, event_queue, font, keyboard.
 */
status allegro_init(Allegro *allegro) {
	if (!al_init()) {
		return STATUS_ERROR_ALLEGRO_INIT;
	}

	al_set_new_display_flags(WINDOW_MODE);

	allegro->display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!allegro->display) {
		return STATUS_ERROR_ALLEGRO_DISPLAY;
	}

	allegro->event_queue = al_create_event_queue();
	if (!allegro->event_queue) {
		return STATUS_ERROR_ALLEGRO_EVENT_QUEUE;
	}

	allegro->timer = al_create_timer(FPS);
	if (!allegro->timer) {
		return STATUS_ERROR_ALLEGRO_TIMER;
	}

	if (!al_init_image_addon()) {
		return STATUS_ERROR_ALLEGRO_IMAGE;
	}

	if (!al_init_font_addon() || !al_init_ttf_addon()) {
		return STATUS_ERROR_ALLEGRO_FONT;
	}

	allegro->font = al_load_ttf_font(ALLEGRO_FONT_FILE, ALLEGRO_FONT_DEFAULT_SIZE, 0);
	if (!allegro->font) {
		return STATUS_ERROR_ALLEGRO_FONT;
	}

	if (!al_install_keyboard()) {
		return STATUS_ERROR_ALLEGRO_KEYBOARD;
	}

	if (!al_install_audio()) {
		return STATUS_ERROR_ALLEGRO_AUDIO;
	}

	al_clear_to_color(al_color_html(ALLEGRO_COLOR_DARK));
	al_flip_display();

	al_register_event_source(allegro->event_queue, al_get_keyboard_event_source());
	al_register_event_source(allegro->event_queue, al_get_display_event_source(allegro->display));
	al_register_event_source(allegro->event_queue, al_get_timer_event_source(allegro->timer));
	al_start_timer(allegro->timer);

	return STATUS_OK_ALLEGRO;
}

/**
 * Destroy Allegro config structure and free the memory.
 */
void allegro_destroy(Allegro *allegro) {
	al_destroy_display(allegro->display);
	al_destroy_event_queue(allegro->event_queue);
	al_destroy_timer(allegro->timer);
	al_shutdown_font_addon();
	al_shutdown_image_addon();
	al_uninstall_keyboard();
	al_uninstall_audio();
	al_uninstall_system();

	free(allegro);
}

/**
 * Display an error message to the screen.
 */
void allegro_message(Allegro *allegro, AllegroMessages type, char *message) {
	al_clear_to_color(al_color_html(ALLEGRO_COLOR_DARK));
	al_draw_text(
		allegro->font,
		al_color_html(ALLEGRO_COLOR_ERROR),
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, message
	);

	al_flip_display();
}

void allegro_display_error(Allegro *allegro, status allegro_status) {
	if (allegro_status != STATUS_ERROR_ALLEGRO_INIT) {
		allegro_message(allegro, ALLEGRO_MESSAGE_ERROR, "ERROR INITIALIZING ALLEGRO");
	}
	else if (allegro_status == STATUS_ERROR_ALLEGRO_DISPLAY) {
		allegro_message(allegro, ALLEGRO_MESSAGE_ERROR, "ERROR INITIALIZING THE DISPLAY");
	}
	else if (allegro_status == STATUS_ERROR_ALLEGRO_EVENT_QUEUE) {
		allegro_message(allegro, ALLEGRO_MESSAGE_ERROR, "ERROR INITIALIZING THE EVENT QUEUE");
	}
	else if (allegro_status == STATUS_ERROR_ALLEGRO_TIMER) {
		allegro_message(allegro, ALLEGRO_MESSAGE_ERROR, "ERROR INITIALIZING THE TIMER");
	}
	else if (allegro_status == STATUS_ERROR_ALLEGRO_FONT) {
		allegro_message(allegro, ALLEGRO_MESSAGE_ERROR, "ERROR INITIALIZING THE FONT");
	}
	else if (allegro_status == STATUS_ERROR_ALLEGRO_IMAGE) {
		allegro_message(allegro, ALLEGRO_MESSAGE_ERROR, "ERROR INITIALIZING THE IMAGE ADDOON");
	}
	else if (allegro_status == STATUS_ERROR_ALLEGRO_KEYBOARD) {
		allegro_message(allegro, ALLEGRO_MESSAGE_ERROR, "ERROR INSTALLING THE KEYBOARD");
	}
	else if (allegro_status == STATUS_ERROR_ALLEGRO_AUDIO) {
		allegro_message(allegro, ALLEGRO_MESSAGE_ERROR, "ERROR INSTALLING THE AUDIO ADDON");
	}
}

/**
 * Wait for a keypress to occur in Allegro's Event Queue.
 */
void allegro_wait_keypress(ALLEGRO_EVENT_QUEUE *event_queue) {
	ALLEGRO_EVENT event = { .type = ALLEGRO_EVENT_KEY_UP };

	while (event.keyboard.keycode != ALLEGRO_KEY_ESCAPE) {
		al_wait_for_event(event_queue, &event);
	}
}