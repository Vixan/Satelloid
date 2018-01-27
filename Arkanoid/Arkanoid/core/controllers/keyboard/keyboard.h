#pragma once

#include <stdlib.h>
#include <allegro5/allegro.h>

#include "../../../globals/status.h"
#include "../../../core/allegro/allegro.h"
#include "../../../models/player/player.h"
#include "../../../models/block/block.h"
#include "../../../models/ball/ball.h"

const enum ControlKeys {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE
};

status handle_player_movement(Allegro *allegro, bool keys[], Player *player);
status handle_keyboard(Allegro *allegro, bool keys[], ALLEGRO_EVENT event, Player *player, Ball *ball);