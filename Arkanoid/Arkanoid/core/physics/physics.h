#pragma once

#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>

#include "../../core/allegro/allegro.h"
#include "../../globals/status.h"
#include "../../models/object/object.h"
#include "../../models/sprite/sprite.h"
#include "../../models/player/player.h"
#include "../../models/block/block.h"
#include "../../models/ball/ball.h"

static const int BLOCK_COLLISION_VELOCITY_RATE_DEFAULT = 20;

bool value_in_range(int value, int min, int max);
bool objects_overlap(Object *object1, Object *object2);
status handle_physics_ball_bounds(Ball *ball);
status handle_physics_ball_block(Ball *ball, Block *block);
status handle_physics_ball_player(Ball *ball, Player *player);