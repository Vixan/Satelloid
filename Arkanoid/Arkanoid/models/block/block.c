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
status destroy_block(Block *block) {
	if (!block) {
		return STATUS_ERROR_SETVALUE;
	}

	free(block->object);
	al_destroy_bitmap(block->sprite->image);
	free(block->sprite);
	free(block);

	return STATUS_OK_SETVALUE;
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
	if (!block || !block->sprite) {
		return NULL;
	}

	return block->sprite;
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
status draw_block(Block *block, unsigned int current_frame) {
	if (!block) {
		return STATUS_ERROR_SETVALUE;	
	}

	Position block_position = get_object_position(get_block_object(block));

	al_draw_tinted_scaled_rotated_bitmap_region(
		get_sprite_image(get_block_sprite(block)),
		BLOCK_WIDTH * current_frame,
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