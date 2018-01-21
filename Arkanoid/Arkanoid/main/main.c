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
	if (allegro_status != STATUS_OK_ALLEGRO) {
		allegro_display_error(allegro, allegro_status);
		allegro_wait_keypress(allegro->event_queue);
	}

	Player *player = create_player(
		create_object(0, 0, 10, 10, OBJECT_DIRECTION_DEFAULT, OBJECT_VELOCITY_DEFAULT),
		create_sprite(
			(char *)PLAYER_IMAGE_DEFAULT_PATH, 
			(unsigned int)SPRITE_FRAME_MIN_DEFAULT, 
			(unsigned int)SPRITE_FRAME_MAX_DEFAULT, 
			(unsigned int)SPRITE_FRAME_CURRENT_DEFAULT),
		PLAYER_HP_DEFAULT,
		PLAYER_SCORE_DEFAULT
	);

	draw_player(player, 0);
	al_flip_display();

	allegro_wait_keypress(allegro->event_queue);

	allegro_destroy(allegro);

	return STATUS_OK_EXIT;
}