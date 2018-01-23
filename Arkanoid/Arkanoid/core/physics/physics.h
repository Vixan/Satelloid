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

static const int BLOCK_COLLISION_VELOCITY_DECREASE_RATE_DEFAULT = 1;

status handle_physics_ball_bounds(Ball *ball);
status handle_physics_ball_block(Ball *ball, Block *block);