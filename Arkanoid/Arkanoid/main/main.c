#include "./main.h"

/**
 * The application main/root function.
 */
status main(int argc, char **argv) {
	Allegro *allegro = allegro_create();
	status allegro_status = STATUS_OK_ALLEGRO;

	if (!allegro) {
		return STATUS_ERROR_EXIT;
	}

	allegro_status = allegro_init(allegro);

	if (allegro_status != STATUS_ERROR_ALLEGRO_INIT) {
		allegro_message(allegro, ALLEGRO_MESSAGE_ERROR, "ERROR INITIALIZING ALLEGRO");
	}
	else if (allegro_status == STATUS_ERROR_ALLEGRO_DISPLAY) {
		allegro_message(allegro, ALLEGRO_MESSAGE_ERROR, "ERROR INITIALIZING THE DISPLAY");
	}

	allegro_wait_keypress(allegro->event_queue);
	allegro_destroy(allegro);

	return STATUS_OK_EXIT;
}