#include "./menu.h"

/**
 * Display Main Menu options.
 */
status display_menu(Allegro *allegro, int choice) {
	al_clear_to_color(al_color_html(ALLEGRO_COLOR_DARK));

	if (!al_init_primitives_addon()) {
		return STATUS_ERROR_ALLEGRO_PRIMITIVES;
	}

	al_draw_filled_rectangle(0, ALLEGRO_FONT_SIZE_SMALL, 16, ALLEGRO_FONT_SIZE_SMALL * 9, al_color_html(ALLEGRO_COLOR_PRIMARY));

	for (int i = MENU_NONE; i < MENU_EXIT; i++) {
		al_draw_text(
			allegro->font,
			al_color_html(i == (choice - 1) ? ALLEGRO_COLOR_PRIMARY : ALLEGRO_COLOR_DEFAULT),
			ALLEGRO_FONT_SIZE_NORMAL,
			i * ALLEGRO_FONT_SIZE_LARGE + ALLEGRO_FONT_SIZE_NORMAL,
			ALLEGRO_ALIGN_LEFT, menu_options[i]
		);
	}

	ALLEGRO_FONT *font_dev = al_load_ttf_font(ALLEGRO_FONT_FILE, ALLEGRO_FONT_SIZE_SMALL, 0);
	al_draw_text(
		font_dev,
		al_color_html(ALLEGRO_COLOR_TEXT),
		2 * ALLEGRO_FONT_SIZE_SMALL,
		SCREEN_HEIGHT - 2 * ALLEGRO_FONT_SIZE_SMALL,
		ALLEGRO_ALIGN_LEFT,
		"Developed by "GAME_DEVELOPER_NAME
	);

	al_draw_text(
		font_dev,
		al_color_html(ALLEGRO_COLOR_TEXT),
		2 * ALLEGRO_FONT_SIZE_SMALL,
		SCREEN_HEIGHT - PLAYER_HEIGHT - 32,
		ALLEGRO_ALIGN_LEFT,
		GAME_VERSION
	);

	ALLEGRO_FONT *font_game = al_load_ttf_font(ALLEGRO_FONT_FILE, ALLEGRO_FONT_SIZE_HUGE, 0);
	al_draw_text(
		font_game,
		al_color_html(ALLEGRO_COLOR_PRIMARY),
		2 * ALLEGRO_FONT_SIZE_SMALL,
		SCREEN_HEIGHT - 2 * PLAYER_HEIGHT - 32,
		ALLEGRO_ALIGN_LEFT,
		GAME_NAME
	);

	ALLEGRO_BITMAP *player_image = al_load_bitmap(PLAYER_IMAGE_DEFAULT_PATH);
	if (!player_image) {
		return STATUS_ERROR_SETVALUE;
	}
	al_draw_tinted_scaled_rotated_bitmap_region(
		player_image, 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT, al_map_rgb(255, 255, 255), 0, 0,
		SCREEN_WIDTH / 2 + PLAYER_WIDTH / 2, SCREEN_HEIGHT - 1.5 * PLAYER_HEIGHT, ALLEGRO_SCALE_DEFAULT, ALLEGRO_SCALE_DEFAULT, 0, 0
	);

	al_destroy_font(font_dev);
	al_destroy_font(font_game);

	al_destroy_bitmap(player_image);
	al_flip_display();


	return STATUS_OK_SETVALUE;
}

/**
 * Handle Main Menu navigation and option selection.
 */
int handle_menu(Allegro *allegro) {
	int choice = MENU_START;
	int selected = MENU_NONE;

	al_start_timer(allegro->timer);
	while (!selected) {
		ALLEGRO_EVENT event = { .type = ALLEGRO_KEY_0 };
		al_wait_for_event(allegro->event_queue, &event);

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				if (choice > MENU_START) {
					choice--;
				}
				break;
			case ALLEGRO_KEY_DOWN:
				if (choice < MENU_EXIT) {
					choice++;
				}
				break;
			case ALLEGRO_KEY_ENTER:
				selected = choice;
				break;
			}
		}
		if (event.type == ALLEGRO_EVENT_TIMER) {
			display_menu(allegro, choice);
		} 
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit(STATUS_OK_EXIT);
		}
	}

	al_stop_timer(allegro->timer);
	al_shutdown_font_addon();

	return selected;
}