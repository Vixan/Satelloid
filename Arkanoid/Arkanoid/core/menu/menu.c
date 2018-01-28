#include "./menu.h"

/**
 * Display Main Menu options.
 */
status display_menu(Allegro *allegro, int choice, ALLEGRO_FONT *font_dev, ALLEGRO_FONT *font_game) {
	al_clear_to_color(al_color_html(ALLEGRO_COLOR_DARK));

	if (!al_init_primitives_addon()) {
		return STATUS_ERROR_ALLEGRO_PRIMITIVES;
	}

	al_draw_filled_rectangle(0, ALLEGRO_FONT_SIZE_SMALL, 16, ALLEGRO_FONT_SIZE_SMALL * 9, al_color_html(ALLEGRO_COLOR_PRIMARY));

	for (int i = MENU_NONE; i < MENU_EXIT; i++) {
		al_draw_text(
			allegro->font,
			al_color_html(i == (choice - 1) ? ALLEGRO_COLOR_PRIMARY : ALLEGRO_COLOR_DARK_SECONDARY),
			ALLEGRO_FONT_SIZE_NORMAL,
			i * ALLEGRO_FONT_SIZE_LARGE + ALLEGRO_FONT_SIZE_NORMAL,
			ALLEGRO_ALIGN_LEFT, menu_options[i]
		);
	}

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

	ALLEGRO_FONT *font_dev = al_load_ttf_font(ALLEGRO_FONT_FILE, ALLEGRO_FONT_SIZE_SMALL, 0);
	ALLEGRO_FONT *font_game = al_load_ttf_font(ALLEGRO_FONT_FILE, ALLEGRO_FONT_SIZE_HUGE, 0);

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
			display_menu(allegro, choice, font_dev, font_game);

		}
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit(STATUS_OK_EXIT);
		}
	}

	al_destroy_font(font_dev);
	al_destroy_font(font_game);
	al_stop_timer(allegro->timer);

	return selected;
}

/**
 * Split a string with the specified separator characters.
 */
status split_string(char *arr[], char* line, char *separator) {
	char *ch = strtok(line, separator);

	for (int i = 0; ch != NULL; i++) {
		arr[i] = ch;
		ch = strtok(NULL, separator);

	}

	return STATUS_OK_SETVALUE;
}

/**
 * Read the Game Scoreboard from the .CSV file.
 */
Score *read_scoreboard(Score *score) {
	FILE *file = NULL;
	char *buffer = malloc(SCOREBOARD_FIELD_SIZE);
	char *line = NULL;
	char *split_line[SCOREBOARD_MAX_FIELDS];
	char *separator = ";";
	Score *head = NULL;

	if (!(file = fopen(SCOREBOARD_FILE_NAME, "r"))) {
		return NULL;
	}

	for (int i = 0; fgets(buffer, SCOREBOARD_FIELD_SIZE, file); i++) {
		line = _strdup(buffer);
		split_string(split_line, line, separator);

		score[i].name = malloc(strlen(split_line[0]) + 1);
		score[i].date = malloc(strlen(split_line[1]) + 1);
		score[i].score = malloc(strlen(split_line[2]) + 1);

		strcpy(score[i].name, split_line[0]);
		strcpy(score[i].date, split_line[1]);
		strcpy(score[i].score, split_line[2]);
	}

	free(buffer);
	buffer = NULL;
	fclose(file);

	return score;
}

/**
* Write the current obtained score to the Scoreboard .CSV file.
*/
status write_score(char *player_name, int score) {
	FILE *file = NULL;
	time_t current_time = time(NULL);
	struct tm *tm = localtime(&current_time);
	int buffer_size = 17;
	char *date = malloc(buffer_size);
	strftime(date, buffer_size, "%d.%m.%Y %H:%M", tm);

	if (!(file = fopen(SCOREBOARD_FILE_NAME, "a"))) {
		return STATUS_ERROR_FILE;
	}

	fprintf(file, "\n%s;", player_name);
	fprintf(file, "%s;", date);
	fprintf(file, "%d", score);

	fclose(file);

	return STATUS_OK_SETVALUE;
}

/**
 * Display the scoreboard read from the file.
 */
status show_scoreboard(Allegro *allegro, Score *scoreboard, int total_records) {
	al_clear_to_color(al_color_html(ALLEGRO_COLOR_DARK));

	if (!scoreboard || !allegro) {
		return STATUS_ERROR_SETVALUE;
	}

	for (int i = 0; i < SCOREBOARD_MAX_FIELDS; i++) {
		al_draw_text(
			allegro->font,
			al_color_html(ALLEGRO_COLOR_PRIMARY),
			i * (ALLEGRO_FONT_SIZE_HUGE + 256) + ALLEGRO_FONT_SIZE_NORMAL,
			ALLEGRO_FONT_SIZE_NORMAL,
			ALLEGRO_ALIGN_LEFT,
			SCOREBOARD_FIELDS[i]
		);
	}

	for (int i = 0; i < total_records; i++) {
		al_draw_text(
			allegro->font,
			al_color_html(ALLEGRO_COLOR_DEFAULT),
			ALLEGRO_FONT_SIZE_NORMAL,
			i * ALLEGRO_FONT_SIZE_NORMAL + 3 * ALLEGRO_FONT_SIZE_NORMAL,
			ALLEGRO_ALIGN_LEFT,
			scoreboard[i].name
		);
		al_draw_text(
			allegro->font,
			al_color_html(ALLEGRO_COLOR_TEXT),
			(ALLEGRO_FONT_SIZE_HUGE + 256) + ALLEGRO_FONT_SIZE_NORMAL,
			i * ALLEGRO_FONT_SIZE_NORMAL + 3 * ALLEGRO_FONT_SIZE_NORMAL,
			ALLEGRO_ALIGN_LEFT,
			scoreboard[i].date
		);
		al_draw_text(
			allegro->font,
			al_color_html(ALLEGRO_COLOR_TEXT),
			2 * (ALLEGRO_FONT_SIZE_HUGE + 256) + ALLEGRO_FONT_SIZE_NORMAL,
			i * ALLEGRO_FONT_SIZE_NORMAL + 3 * ALLEGRO_FONT_SIZE_NORMAL,
			ALLEGRO_ALIGN_LEFT,
			scoreboard[i].score
		);
	}

	al_flip_display();

	return STATUS_OK_SETVALUE;
}

/**
 * Retrieve the total number of records from the file.
 */
int count_scoreboard_records() {
	FILE *file = NULL;
	char *buffer = malloc(SCOREBOARD_FIELD_SIZE);
	int total_records = 0;

	if (!(file = fopen(SCOREBOARD_FILE_NAME, "r"))) {
		return 0;
	}

	while (fgets(buffer, 256, file)) {
		total_records++;
	}

	return total_records;
}