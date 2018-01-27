#pragma once

#include <stdio.h>
#include <conio.h>

#include "../globals/status.h"
#include "../core/allegro/allegro.h"
#include "../models/player/player.h"
#include "../models/ball/ball.h"
#include "../models/block/block.h"
#include "../core/controllers/keyboard/keyboard.h"
#include "../core/physics/physics.h"
#include "../core/level/level.h"
#include "../core/menu/menu.h"

status show_menu(Allegro *allegro);
status show_player_score(Allegro *allegro, Player *player, ALLEGRO_FONT *score_font);
status start_game(Allegro *allegro, bool level[ROWS][COLS]);