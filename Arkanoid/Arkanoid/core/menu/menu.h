#pragma once

#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "../allegro/allegro.h"
#include "../../globals/status.h"
#include "../../models/player/player.h"
#include "../../globals/game.h"

enum MENU_OPTIONS {
	MENU_NONE,
	MENU_START,
	MENU_SCOREBOARD,
	MENU_CREDTS,
	MENU_EXIT
};

static const char *menu_options[MENU_EXIT + 1] = {
	"START NEW GAME",
	"SCOREBOARD",
	"CREDITS AND DEVELOPMENT",
	"EXIT GAME"
};

typedef struct Score {
	char *name;
	char *date;
	char *score;
} Score;

static const char *SCOREBOARD_FILE_NAME = "./globals/scoreboard.csv";
#define SCOREBOARD_MAX_RECORDS 32
#define SCOREBOARD_MAX_FIELDS 3
#define SCOREBOARD_FIELD_SIZE 256

static const char *SCOREBOARD_FIELDS[SCOREBOARD_MAX_FIELDS] = {
	"NAME",
	"DATE",
	"SCORE"
};

status display_menu(Allegro *allegro, int choice, ALLEGRO_FONT *font_dev, ALLEGRO_FONT *font_game);
int handle_menu(Allegro *allegro);

status split_string(char *arr[], char* line, char *separator);
Score *read_scoreboard(Score *score);
status show_scoreboard(Allegro *allegro, Score *scoreboard, int total_records);
int count_scoreboard_records();