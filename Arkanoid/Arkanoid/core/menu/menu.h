#pragma once

#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "../allegro/allegro.h"
#include "../../globals/status.h"
#include "../../models/player/player.h"

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

status display_menu(Allegro *allegro, int choice);
int handle_menu(Allegro *allegro);