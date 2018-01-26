#pragma warning(disable: 4096)
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

	show_menu(allegro);

	allegro_destroy(allegro);

	return STATUS_OK_EXIT;
}

/**
 * Go to the Main Menu.
 */
status show_menu(Allegro *allegro) {
	int selected = false;
	int menu_choice = MENU_NONE;

	while (menu_choice != MENU_EXIT) {
		menu_choice = handle_menu(allegro);
		if (menu_choice == MENU_START) {
			if (start_game(allegro) == STATUS_ERROR_EXIT) {
				return STATUS_ERROR_EXIT;
			}
			break;
		}
	}

	return STATUS_OK_EXIT;
}

/**
 * Display the Player score on the game screen.
 */
status show_player_score(Allegro *allegro, Player *player, ALLEGRO_FONT *score_font) {
	char *score = malloc(16);
	sprintf(score, "%d", get_player_score(player));

	al_draw_text(
		score_font,
		al_color_html(ALLEGRO_COLOR_DARK_SECONDARY),
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2,
		ALLEGRO_ALIGN_CENTRE,
		score
	);

	free(score);

	return STATUS_OK_SETVALUE;
}

/**
 * Start the game.
 */
status start_game(Allegro *allegro) {
	Player *player = create_player(
		create_object(
			SCREEN_WIDTH / 2 + PLAYER_WIDTH / 2,
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

	bool running = true;
	bool keys[4] = { false, false, false, false };
	bool blocks_level[ROWS][COLS];
	ALLEGRO_FONT *score_font = al_load_font(ALLEGRO_FONT_FILE, 128, 0);

	memcpy(blocks_level, LEVEL_2, sizeof(blocks_level));

	int blocks_max = get_max_level_blocks(blocks_level);
	Block **blocks = create_level(blocks_level, blocks_max);

	set_ball_direction(ball, 1, 1);

	al_start_timer(allegro->timer);

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

		show_player_score(allegro, player, score_font);

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
			if (ball) {
				for (int i = 0; i < blocks_max; i++) {
					if (blocks[i]) {
						handle_physics_ball_block(ball, blocks[i], player);

						if (get_block_hp(blocks[i]) <= 0) {
							if (get_block_hp(blocks[i]) == 0 && animate_block(blocks[i])) {
								blocks[i] = destroy_block(blocks[i]);
							}
						}
					}
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
			if (show_menu(allegro) == STATUS_OK_EXIT) {
				return STATUS_OK_EXIT;
			}
		}
	}

	destroy_ball(ball);

	for (int i = 0; i < blocks_max; i++) {
		Block *block = *(blocks + i);
		destroy_block(block);
	}

	free(blocks);
	al_destroy_font(score_font);

	destroy_player(player);

	return STATUS_OK_EXIT;
}