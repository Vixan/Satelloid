#pragma once

#include <stdlib.h>
#include <allegro5/allegro.h>

#include "../../globals/status.h"
#include "../object/object.h"
#include "../sprite/sprite.h"

typedef struct Block {
	Object *object;
	Sprite *sprite;
	unsigned int hp;
} Block;

static const unsigned int BLOCK_HP_DEFAULT = 1;
static const char *BLOCK_IMAGE_DEFAULT_PATH = "./assets/images/block.png";

Block *create_block(Object *object, Sprite *sprite, unsigned int hp);
status destroy_block(Block *block);

status set_block_object(Block *block, Object *object);
Object *get_block_object(Block *block);

status set_block_sprite(Block *block, Sprite *sprite);
Sprite *get_block_sprite(Block *block);

status set_block_hp(Block *block, unsigned int hp);
unsigned int get_block_hp(Block *block);

status draw_block(Block *block);