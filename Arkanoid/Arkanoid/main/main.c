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
	status game_status = STATUS_NEW_GAME;
	ALLEGRO_FONT *game_over_font = al_load_font(ALLEGRO_FONT_FILE, ALLEGRO_FONT_SIZE_HUGE, 0);
	ALLEGRO_SAMPLE *game_over_sample = al_load_sample(ALLEGRO_GAMEOVER_SAMPLE_FILE);
	ALLEGRO_SAMPLE_ID background_sample_id;
	ALLEGRO_SAMPLE_ID game_over_sample_id;

	al_play_sample(allegro->music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &background_sample_id);

	while (menu_choice != MENU_EXIT) {
		menu_choice = handle_menu(allegro);
		if (menu_choice == MENU_START) {
			game_status = start_game(allegro, (bool(*)[COLS])LEVEL_2);

			if (game_status == STATUS_ERROR_EXIT) {
				return STATUS_ERROR_EXIT;
			}

			if (game_status == STATUS_OK_EXIT) {
				show_menu(allegro);
			}

			if (game_status == STATUS_GAME_OVER) {
				char *final_message = malloc(SCORE_MAX_DIGITS + 50);
				sprintf(final_message, "%d", final_score);
				strcat(final_message, " points");

				al_clear_to_color(al_color_html(ALLEGRO_COLOR_DARK));
				al_draw_text(
					game_over_font,
					al_color_html(ALLEGRO_COLOR_ACCENT1),
					SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2 - ALLEGRO_FONT_SIZE_HUGE,
					ALLEGRO_ALIGN_CENTRE,
					"SATELLITE MISSION OVER"
				);

				al_draw_text(
					allegro->font,
					al_color_html(ALLEGRO_COLOR_TEXT),
					SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					ALLEGRO_ALIGN_CENTRE,
					final_message
				);

				al_draw_text(
					allegro->font,
					al_color_html(ALLEGRO_COLOR_DARK_SECONDARY),
					SCREEN_WIDTH / 2,
					SCREEN_HEIGHT - 2 * ALLEGRO_FONT_SIZE_HUGE,
					ALLEGRO_ALIGN_CENTRE,
					"Press ESC to return to MENU"
				);

				al_stop_sample(&background_sample_id);
				al_play_sample(game_over_sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &game_over_sample_id);

				al_flip_display();
				allegro_wait_keypress(allegro->event_queue);
				al_destroy_font(game_over_font);
				al_stop_sample(&game_over_sample_id);
				al_destroy_sample(game_over_sample);

				show_menu(allegro);
			}

			break;
		}
	}

	return STATUS_OK_EXIT;
}

/**
 * Start the game.
 */
status start_game(Allegro *allegro, bool level[ROWS][COLS]) {
	Player *player = create_player(
		create_object(
			SCREEN_WIDTH / 2 + PLAYER_WIDTH / 2,
			SCREEN_HEIGHT - 1.5 * PLAYER_HEIGHT,
			PLAYER_HEIGHT,
			PLAYER_WIDTH,
			OBJECT_DIRECTION_DEFAULT,
			OBJECT_DIRECTION_DEFAULT,
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
			get_player_position(player).y - PLAYER_HEIGHT / 2 - 1,
			BALL_HEIGHT,
			BALL_WIDTH,
			OBJECT_DIRECTION_DEFAULT,
			OBJECT_DIRECTION_DEFAULT,
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

	status game_status = STATUS_GAME_RUNNING;
	bool keys[4] = { false, false, false, false };
	bool blocks_level[ROWS][COLS];
	ALLEGRO_FONT *score_font = al_load_font(ALLEGRO_FONT_FILE, 128, 0);
	ALLEGRO_SAMPLE *effect_sample = al_load_sample(ALLEGRO_EFFECT_SAMPLE_FILE);
	ALLEGRO_BITMAP *player_hp_image = al_load_bitmap(PLAYER_HP_IMAGE_PATH);

	memcpy(blocks_level, level, sizeof(blocks_level));

	int blocks_max = get_max_level_blocks(blocks_level);
	Block **blocks = create_level(blocks_level, blocks_max);

	al_start_timer(allegro->timer);

	while (game_status == STATUS_GAME_RUNNING) {
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
		show_player_hp(player_hp_image, player, PLAYER_HEIGHT);

		al_wait_for_event(allegro->event_queue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER) {
			if (get_player_hp(player) == 0) {
				game_status = STATUS_GAME_OVER;
				break;
			}

			if (handle_player_movement(allegro, keys, player) == STATUS_ERROR_SETVALUE) {
				return STATUS_ERROR_EXIT;
			}

			if (ball) {
				handle_physics_ball_bounds(ball, player);
			}
			if (ball && player) {
				handle_physics_ball_player(ball, player);

			}
			if (ball && blocks) {
				for (int i = 0; i < blocks_max; i++) {
					if (blocks[i]) {
						if (handle_physics_ball_block(ball, blocks[i], player, effect_sample) == STATUS_OK_SETVALUE) {
							if (get_block_hp(blocks[i]) == 0 && animate_block(blocks[i])) {
								blocks[i] = destroy_block(blocks[i]);
							}
						}
					}
				}
			}

			if (get_ball_direction(ball).x && get_ball_direction(ball).y) {
				set_ball_position(
					ball,
					get_ball_position(ball).x + get_ball_direction(ball).x * get_ball_velocity(ball),
					get_ball_position(ball).y + get_ball_direction(ball).y * get_ball_velocity(ball)
				);
			}
			else {
				set_ball_position(
					ball,
					get_player_position(player).x + PLAYER_WIDTH / 2 - BALL_WIDTH / 2,
					get_player_position(player).y - PLAYER_HEIGHT / 2 - 1
				);
			}

		}
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			game_status = STATUS_OK_EXIT;
			break;
		}
		else if (handle_keyboard(allegro, keys, event, player, ball) == STATUS_OK_EXIT) {
			game_status = STATUS_OK_EXIT;
			break;
		}
	}

	destroy_ball(ball);

	for (int i = 0; i < blocks_max; i++) {
		Block *block = *(blocks + i);
		destroy_block(block);
	}

	free(blocks);
	al_destroy_font(score_font);
	al_destroy_sample(effect_sample);
	al_destroy_bitmap(player_hp_image);

	final_score = get_player_score(player);
	destroy_player(player);

	return game_status;
}