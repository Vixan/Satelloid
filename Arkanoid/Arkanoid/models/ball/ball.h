#pragma once

#include <stdlib.h>
#include <allegro5/allegro.h>

#include "../../core/allegro/allegro.h"
#include "../../globals/status.h"
#include "../object/object.h"
#include "../sprite/sprite.h"

typedef struct Ball {
	Object *object;
	Sprite *sprite;
	unsigned int type;
} Ball;

static const unsigned int BALL_TYPE_DEFAULT = 0;
static const char *BALL_IMAGE_DEFAULT_PATH = "./assets/images/ball/ball.png";
static const unsigned int BALL_HEIGHT = 32;
static const unsigned int BALL_WIDTH = 32;

Ball *create_ball(Object *object, Sprite *sprite, unsigned int type);
status destroy_ball(Ball *ball);

status set_ball_object(Ball *ball, Object *object);
Object *get_ball_object(Ball *ball);

status set_ball_sprite(Ball *ball, Sprite *sprite);
Sprite *get_ball_sprite(Ball *ball);

status set_ball_type(Ball *ball, unsigned int type);
unsigned int get_ball_type(Ball *ball);

status draw_ball(Ball *ball, unsigned int current_frame);