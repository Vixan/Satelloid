#include "./sprite.h"

/**
 * Create a Sprite with the specified image and animation frame values.
 */
Sprite *create_sprite(char *image_path, unsigned int min, unsigned int max, unsigned int current) {
	ALLEGRO_BITMAP *image = NULL;
	Sprite *sprite = malloc(sizeof(Sprite));
	if (!sprite) {
		return NULL;
	}

	image = al_load_bitmap(image_path);
	if (!image) {
		return NULL;
	}

	sprite->image = image;
	sprite->frame.min = min;
	sprite->frame.max = max;
	sprite->frame.current = current;
	sprite->frame.count = 0;
	sprite->frame.column = SPRITE_FRAME_COLUMN_DEFAULT;

	return sprite;
}

/**
 * Destroy the Sprite and free up the memory used.
 */
status destroy_sprite(Sprite *sprite) {
	if (!sprite) {
		return STATUS_ERROR_SETVALUE;
	}

	al_destroy_bitmap(sprite->image);
	free(sprite);

	return STATUS_OK_SETVALUE;
}

/**
 * Set the image property of the Sprite.
 */
status set_sprite_image(Sprite *sprite, char *image_path) {
	ALLEGRO_BITMAP *image = al_load_bitmap(image_path);
	if (!sprite) {
		return STATUS_ERROR_SETVALUE;
	}
	if (!image) {
		return STATUS_ERROR_SETVALUE;
	}

	sprite->image = image;

	return STATUS_OK_SETVALUE;
}

/**
 * Retrieve the image property of the Sprite.
 */
ALLEGRO_BITMAP *get_sprite_image(Sprite *sprite) {
	if (!sprite) {
		return NULL;
	}

	return sprite->image;
}

/**
* Set the first animation frame index of the Sprite.
*/
status set_sprite_min_frame(Sprite *sprite, unsigned int min) {
	if (!sprite) {
		return STATUS_ERROR_SETVALUE;
	}

	sprite->frame.min = min;

	return STATUS_OK_SETVALUE;
}

/**
 * Retrieve the first animation frame index of the Sprite.
 */
unsigned int get_sprite_min_frame(Sprite *sprite) {
	if (!sprite) {
		return SPRITE_FRAME_MIN_DEFAULT;
	}

	return sprite->frame.min;
}


/**
* Set the last animation frame index of the Sprite.
*/
status set_sprite_max_frame(Sprite *sprite, unsigned int max) {
	if (!sprite) {
		return STATUS_ERROR_SETVALUE;
	}

	sprite->frame.max = max;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the last animation frame index of the Sprite.
*/
unsigned int get_sprite_max_frame(Sprite *sprite) {
	if (!sprite) {
		return SPRITE_FRAME_MAX_DEFAULT;
	}

	return sprite->frame.max;
}

/**
* Set the current animation frame index of the Sprite.
*/
status set_sprite_current_frame(Sprite *sprite, unsigned int current) {
	if (!sprite) {
		return STATUS_ERROR_SETVALUE;
	}

	sprite->frame.current = current;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the current animation frame index of the Sprite.
*/
unsigned int get_sprite_current_frame(Sprite *sprite) {
	if (!sprite) {
		return SPRITE_FRAME_MAX_DEFAULT;
	}

	return sprite->frame.current;
}

/**
* Set the animation frame count.
*/
status set_sprite_frame_count(Sprite *sprite, unsigned int count) {
	if (!sprite) {
		return STATUS_ERROR_SETVALUE;
	}

	sprite->frame.count = count;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the animation frame count.
*/
unsigned int get_sprite_frame_count(Sprite *sprite) {
	if (!sprite) {
		return SPRITE_FRAME_MIN_DEFAULT;
	}

	return sprite->frame.count;
}

/**
* Set the spritesheet animation column.
*/
status set_sprite_frame_column(Sprite *sprite, unsigned int column) {
	if (!sprite) {
		return STATUS_ERROR_SETVALUE;
	}

	sprite->frame.column = column;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve spritesheet animation column.
*/
unsigned int get_sprite_frame_column(Sprite *sprite) {
	if (!sprite) {
		return SPRITE_FRAME_COLUMN_DEFAULT;
	}

	return sprite->frame.column;
}