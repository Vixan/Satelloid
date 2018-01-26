#pragma once

#include <stdlib.h>
#include <allegro5/allegro.h>

#include "../../core/allegro/allegro.h"
#include "../../globals/status.h"
#include "../object/object.h"
#include "../sprite/sprite.h"

typedef struct Block {
	Object *object;
	Sprite *sprite;
	unsigned int hp;
} Block;

static const unsigned int BLOCK_HP_DEFAULT = 1;
static const char *BLOCK_IMAGE_DEFAULT_PATH = "./assets/images/block/block.png";
static const unsigned int BLOCK_HEIGHT = 64;
static const unsigned int BLOCK_WIDTH = 64;
static const unsigned int BLOCK_ANIMATION_DELAY = 2;
static const unsigned int BLOCK_GAP = 16;

Block *create_block(Object *object, Sprite *sprite, unsigned int hp);
Block *destroy_block(Block *block);

status set_block_object(Block *block, Object *object);
Object *get_block_object(Block *block);

status set_block_position(Block *block, unsigned int x, unsigned int y);
Position get_block_position(Block *block);

status set_block_size(Block *block, unsigned int height, unsigned int width);
Size get_block_size(Block *block);

status set_block_sprite(Block *block, Sprite *sprite);
Sprite *get_block_sprite(Block *block);

status set_block_current_frame(Block *block, unsigned int current);
unsigned int get_block_current_frame(Block *block);

bool animate_block(Block *block);

status set_block_hp(Block *block, unsigned int hp);
unsigned int get_block_hp(Block *block);

status draw_block(Block *block);