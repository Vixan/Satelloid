#include "./block.h"

/**
* Create a Block with the specified game Object and Sprite properties.
*/
Block *create_block(Object *object, Sprite *sprite, unsigned int hp) {
	Block *block = malloc(sizeof(Block));
	if (!block || !object || !sprite) {
		return NULL;
	}

	block->object = object;
	block->sprite = sprite;
	block->hp = hp;

	return block;
}

/**
* Destroy the Block and free up the memory used.
*/
Block *destroy_block(Block *block) {
	if (!block) {
		return NULL;
	}

	free(block->object);
	al_destroy_bitmap(block->sprite->image);
	free(block->sprite);
	free(block);

	block->object = NULL;
	block->sprite = NULL;
	block = NULL;

	return block;
}

/**
* Set the Block's game Object properties.
*/
status set_block_object(Block *block, Object *object) {
	if (!block || !object) {
		return STATUS_ERROR_SETVALUE;
	}

	block->object = object;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Block's game Object.
*/
Object *get_block_object(Block *block) {
	if (!block || !block->object) {
		return NULL;
	}

	return block->object;
}


/**
* Set the Block's position in X and Y coordinates.
*/
status set_block_position(Block *block, unsigned int x, unsigned int y) {
	if (!block) {
		return STATUS_ERROR_SETVALUE;
	}

	if (!set_object_position(get_block_object(block), x, y)) {
		return STATUS_ERROR_SETVALUE;
	}

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Block's position in X and Y coordinates.
*/
Position get_block_position(Block *block) {
	if (!block) {
		return (Position) { .x = 0, .y = 0 };
	}

	return get_object_position(get_block_object(block));
}

/**
* Set the Block's height and width.
*/
status set_block_size(Block *block, unsigned int height, unsigned int width) {
	if (!block) {
		return STATUS_ERROR_SETVALUE;
	}

	if (!set_object_size(get_block_object(block), height, width)) {
		return STATUS_ERROR_SETVALUE;
	}

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Block's height and width.
*/
Size get_block_size(Block *block) {
	if (!block) {
		return (Size) { .height = 0, .width = 0 };
	}

	return get_object_size(get_block_object(block));
}

/**
* Set the Block's Sprite.
*/
status set_block_sprite(Block *block, Sprite *sprite) {
	if (!block || !sprite) {
		return STATUS_ERROR_SETVALUE;
	}

	block->sprite = sprite;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Block's Sprite.
*/
Sprite *get_block_sprite(Block *block) {
	if (!block->sprite) {
		return NULL;
	}

	return block->sprite;
}

/**
* Set the current animation frame index of the Block's sprite.
*/
status set_block_current_frame(Block *block, unsigned int current) {
	if (!block) {
		return STATUS_ERROR_SETVALUE;
	}

	set_sprite_current_frame(get_block_sprite(block), current);

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the current animation frame index of the Block's sprite.
*/
unsigned int get_block_current_frame(Block *block) {
	if (!block) {
		return SPRITE_FRAME_MAX_DEFAULT;
	}

	return get_sprite_current_frame(get_block_sprite(block));
}

/**
 * Run the animation of the Block when destroyed.
 */
bool animate_block(Block *block) {
	if (!block || !block->hp <= 0) {
		return false;
	}

	unsigned int frame_max = get_sprite_max_frame(get_block_sprite(block));

	if (get_sprite_current_frame(get_block_sprite(block)) >= frame_max) {
		return true;
	}

	set_sprite_frame_count(get_block_sprite(block), get_sprite_frame_count(get_block_sprite(block)) + 1);
	if (get_sprite_frame_count(get_block_sprite(block)) >= BLOCK_ANIMATION_DELAY) {
		set_block_current_frame(block, get_block_current_frame(block) + 1);

		set_sprite_frame_count(get_block_sprite(block), SPRITE_FRAME_CURRENT_DEFAULT);
	}

	return false;
}

/**
* Set the Block's HP (Hit Points / Lives).
*/
status set_block_hp(Block *block, unsigned int hp) {
	if (!block) {
		return STATUS_ERROR_SETVALUE;
	}

	block->hp = hp;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Block's HP (Hit Points / Lives).
*/
unsigned int get_block_hp(Block *block) {
	if (!block) {
		return BLOCK_HP_DEFAULT;
	}

	return block->hp;
}

/**
 * Draw the Block's image on the screen.
 */
status draw_block(Block *block) {
	if (!block) {
		return STATUS_ERROR_SETVALUE;
	}

	Position block_position = get_object_position(get_block_object(block));

	al_draw_tinted_scaled_rotated_bitmap_region(
		get_sprite_image(get_block_sprite(block)),
		BLOCK_WIDTH * get_block_current_frame(block),
		0,
		BLOCK_WIDTH,
		BLOCK_HEIGHT,
		al_map_rgb(255, 255, 255),
		0,
		0,
		block_position.x,
		block_position.y,
		1,
		1,
		0,
		0
	);

	return STATUS_OK_SETVALUE;
}