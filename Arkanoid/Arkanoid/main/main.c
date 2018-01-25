#include "./main.h"

/**
 * The application main/root function.
 */
status main(int argc, char **argv) {
	Allegro *allegro = allegro_create();
	status allegro_status = STATUS_OK_ALLEGRO;

	if (!allegro) {
		printf("Could not initialize Allegro");
		_getch();
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
			0,
			0,
			PLAYER_VELOCITY_DEFAULT
		),
		create_sprite(
		(char *)PLAYER_IMAGE_DEFAULT_PATH,
			(unsigned int)SPRITE_FRAME_MIN_DEFAULT,
			(unsigned int)PLAYER_SPRITE_MAX,
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
			0,
			0,
			BALL_VELOCITY_DEFAULT
		),
		create_sprite(
		(char *)BALL_IMAGE_DEFAULT_PATH,
			(unsigned int)SPRITE_FRAME_MIN_DEFAULT,
			(unsigned int)SPRITE_FRAME_MAX_DEFAULT,
			(unsigned int)SPRITE_FRAME_CURRENT_DEFAULT
		),
		BALL_TYPE_DEFAULT
	);

	unsigned int blocks_max = 5;
	unsigned int blocks_level = 0;
	Block **blocks = malloc(sizeof(Block *) * blocks_max);

	for (int i = 0; i < blocks_max; i++) {
		Block *block = create_block(
			create_object(
				0,
				0,
				BLOCK_HEIGHT,
				BLOCK_WIDTH,
				0,
				0,
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

		blocks[i] = block;
		set_block_position(blocks[i], BLOCK_GAP, blocks_level * BLOCK_HEIGHT + BLOCK_HEIGHT);
		
	}

	set_block_position(blocks[0], BLOCK_GAP, 2 * BLOCK_HEIGHT);
	set_block_position(blocks[1], (get_block_position(blocks[1]).x + BLOCK_WIDTH + BLOCK_GAP) + BLOCK_GAP, 2 * BLOCK_HEIGHT);
	set_block_position(blocks[2], (get_block_position(blocks[2]).x + BLOCK_WIDTH + BLOCK_GAP) * 2 + BLOCK_GAP, 2 * BLOCK_HEIGHT);
	set_block_position(blocks[3], (get_block_position(blocks[3]).x + BLOCK_WIDTH + BLOCK_GAP) * 3 + BLOCK_GAP, 2 * BLOCK_HEIGHT);
	set_block_position(blocks[4], (get_block_position(blocks[4]).x + BLOCK_WIDTH + BLOCK_GAP) * 4 + BLOCK_GAP, 2 * BLOCK_HEIGHT);

	bool running = true;
	bool keys[4] = { false, false, false, false };

	al_start_timer(allegro->timer);

	set_ball_direction(ball, 1, 1);
	while (running) {
		ALLEGRO_EVENT event = { .type = ALLEGRO_EVENT_KEY_UP };

		if (player) {
			draw_player(player);
		}
		if (ball) {
			draw_ball(ball);
		}

		for (int i = 0; i < blocks_max; i++) {
			Block *block = *(blocks + i);

			if (block != NULL) {
				draw_block(block);
			}
		}

		al_flip_display();
		al_clear_to_color(al_color_html(ALLEGRO_COLOR_DARK));

		al_wait_for_event(allegro->event_queue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER) {
			if (handle_player_movement(allegro, keys, player) == STATUS_ERROR_SETVALUE) {
				return STATUS_ERROR_EXIT;
			}

			if (ball) {
				handle_physics_ball_bounds(ball);
			}
			if (ball && player) {
				handle_physics_ball_player(ball, player);
			}
			if (ball && blocks) {
				for (int i = 0; i < blocks_max; i++) {
					Block *block = *(blocks + i);
					if (block) {
						handle_physics_ball_block(ball, block);

						if (get_block_hp(block) <= 0) {
							if (animate_block(block)) {
								block = destroy_block(block);
							}
						}
					}

					blocks[i] = block;
				}
			}

			set_ball_position(
				ball,
				get_ball_position(ball).x + get_ball_direction(ball).x * get_ball_velocity(ball),
				get_ball_position(ball).y + get_ball_direction(ball).y * get_ball_velocity(ball)
			);
		}
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			return STATUS_OK_EXIT;
		}
		else if (handle_keyboard(allegro, keys, event, player) == STATUS_OK_EXIT) {
			return STATUS_OK_EXIT;
		}
	}

	destroy_ball(ball);

	for (int i = 0; i < blocks_max; i++) {
		Block *block = *(blocks + i);
		destroy_block(block);
	}
	free(blocks);

	destroy_player(player);

	allegro_destroy(allegro);

	return STATUS_OK_EXIT;
}