#pragma once

#include <stdlib.h>
#include <allegro5/allegro.h>

#include "../../globals/status.h"

typedef struct Frame {
	unsigned int min;
	unsigned int max;
	unsigned int current;
	unsigned int count;
	unsigned int column;
} Frame;

typedef struct Sprite {
	ALLEGRO_BITMAP *image;
	Frame frame;
} Sprite;

static const char *SPRITE_IMAGE_DEFAULT = NULL;
static const unsigned int SPRITE_FRAME_MIN_DEFAULT = 0;
static const unsigned int SPRITE_FRAME_MAX_DEFAULT = 8;
static const unsigned int SPRITE_FRAME_CURRENT_DEFAULT = 0;
static const unsigned int SPRITE_FRAME_COLUMN_DEFAULT = 0;

Sprite *create_sprite(char *image_path, unsigned int min, unsigned int max, unsigned int current);
status destroy_sprite(Sprite *sprite);

status set_sprite_image(Sprite *sprite, char *image_path);
ALLEGRO_BITMAP *get_sprite_image(Sprite *sprite);

status set_sprite_min_frame(Sprite *sprite, unsigned int min);
unsigned int get_sprite_min_frame(Sprite *sprite);

status set_sprite_max_frame(Sprite *sprite, unsigned int max);
unsigned int get_sprite_max_frame(Sprite *sprite);

status set_sprite_current_frame(Sprite *sprite, unsigned int current);
unsigned int get_sprite_current_frame(Sprite *sprite);

status set_sprite_frame_count(Sprite *sprite, unsigned int count);
unsigned int get_sprite_frame_count(Sprite *sprite);

status set_sprite_frame_column(Sprite *sprite, unsigned int column);
unsigned int get_sprite_frame_column(Sprite *sprite);