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
static const int BALL_VELOCITY_DEFAULT = 8;
static const int BALL_VELOCITY_MIN = 2;

Ball *create_ball(Object *object, Sprite *sprite, unsigned int type);
status destroy_ball(Ball *ball);

status set_ball_object(Ball *ball, Object *object);
Object *get_ball_object(Ball *ball);

status set_ball_position(Ball *ball, unsigned int x, unsigned int y);
Position get_ball_position(Ball *ball);

status set_ball_size(Ball *ball, unsigned int height, unsigned int width);
Size get_ball_size(Ball *ball);

status set_ball_direction(Ball *ball, int x, int y);
Direction get_ball_direction(Ball *ball);

status set_ball_velocity(Ball *ball, int velocity);
int get_ball_velocity(Ball *ball);

status set_ball_sprite(Ball *ball, Sprite *sprite);
Sprite *get_ball_sprite(Ball *ball);

status set_ball_current_frame(Ball *ball, unsigned int current);
unsigned int get_ball_current_frame(Ball *ball);

status set_ball_type(Ball *ball, unsigned int type);
unsigned int get_ball_type(Ball *ball);

status draw_ball(Ball *ball);
bool animate_ball(Ball *ball);