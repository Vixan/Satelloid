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
		create_object(
			SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2,
			SCREEN_HEIGHT - 1.5 * PLAYER_HEIGHT,
			PLAYER_HEIGHT,
			PLAYER_WIDTH,
			OBJECT_DIRECTION_DEFAULT,
			PLAYER_VELOCITY_DEFAULT
		),
		create_sprite(
		(char *)PLAYER_IMAGE_DEFAULT_PATH,
			(unsigned int)SPRITE_FRAME_MIN_DEFAULT,
			(unsigned int)SPRITE_FRAME_MAX_DEFAULT,
			(unsigned int)SPRITE_FRAME_CURRENT_DEFAULT
		),
		PLAYER_HP_DEFAULT,
		PLAYER_SCORE_DEFAULT
	);

	Ball *ball = create_ball(
		create_object(
			get_player_position(player).x + PLAYER_WIDTH / 2 - BALL_WIDTH / 2,
			get_player_position(player).y - PLAYER_HEIGHT / 2,
			BALL_HEIGHT,
			BALL_WIDTH,
			OBJECT_DIRECTION_DEFAULT,
			OBJECT_VELOCITY_DEFAULT
		),
		create_sprite(
		(char *)BALL_IMAGE_DEFAULT_PATH,
			(unsigned int)SPRITE_FRAME_MIN_DEFAULT,
			(unsigned int)SPRITE_FRAME_MAX_DEFAULT,
			(unsigned int)SPRITE_FRAME_CURRENT_DEFAULT
		),
		BALL_TYPE_DEFAULT
	);

	Block *block = create_block(
		create_object(
			SCREEN_WIDTH / 2 - BLOCK_WIDTH / 2,
			BLOCK_HEIGHT / 2,
			BLOCK_HEIGHT,
			BLOCK_WIDTH,
			OBJECT_DIRECTION_DEFAULT,
			OBJECT_VELOCITY_DEFAULT
		),
		create_sprite(
		(char *)BLOCK_IMAGE_DEFAULT_PATH,
			(unsigned int)SPRITE_FRAME_MIN_DEFAULT,
			(unsigned int)SPRITE_FRAME_MAX_DEFAULT,
			(unsigned int)SPRITE_FRAME_CURRENT_DEFAULT
		),
		BLOCK_HP_DEFAULT
	);

	bool running = true;
	bool keys[4] = { false, false, false, false };

	al_start_timer(allegro->timer);

	while (running) {
		ALLEGRO_EVENT event = { .type = ALLEGRO_EVENT_KEY_UP };

		if (handle_keyboard(allegro, keys, event, player, ball, block) == STATUS_OK_EXIT) {
			return STATUS_OK_EXIT;
		}
	}

	destroy_ball(ball);
	destroy_block(block);
	destroy_player(player);

	allegro_destroy(allegro);

	return STATUS_OK_EXIT;
}