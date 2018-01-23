#include "./player.h"

/**
 * Create the Player with the specified game Object and Sprite properties.
 */
Player *create_player(Object *object, Sprite *sprite, unsigned int hp, unsigned int score) {
	Player *player = malloc(sizeof(Player));
	if (!player || !object || !sprite) {
		return NULL;
	}

	player->object = object;
	player->sprite = sprite;
	player->hp = hp;
	player->score = score;

	return player;
}

/**
 * Destroy the Player and free up the memory used.
 */
status destroy_player(Player *player) {
	if (!player) {
		return STATUS_ERROR_SETVALUE;
	}

	free(player->object);
	al_destroy_bitmap(player->sprite->image);
	free(player->sprite);
	free(player);

	return STATUS_OK_SETVALUE;
}

/**
* Set the Player's game Object properties.
*/
status set_player_object(Player *player, Object *object) {
	if (!player || !object) {
		return STATUS_ERROR_SETVALUE;
	}

	player->object = object;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Player's game Object.
*/
Object *get_player_object(Player *player) {
	if (!player || !player->object) {
		return NULL;
	}

	return player->object;
}

/**
* Set the Player's position in X and Y coordinates.
*/
status set_player_position(Player *player, unsigned int x, unsigned int y) {
	if (!player) {
		return STATUS_ERROR_SETVALUE;
	}

	if (!set_object_position(get_player_object(player), x, y)) {
		return STATUS_ERROR_SETVALUE;
	}

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Player's position in X and Y coordinates.
*/
Position get_player_position(Player *player) {
	if (!player) {
		return (Position) { .x = 0, .y = 0 };
	}

	return get_object_position(get_player_object(player));
}

/**
* Set the Player's height and width.
*/
status set_player_size(Player *player, unsigned int height, unsigned int width) {
	if (!player) {
		return STATUS_ERROR_SETVALUE;
	}

	if (!set_object_size(get_player_object(player), height, width)) {
		return STATUS_ERROR_SETVALUE;
	}

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Player's height and width.
*/
Size get_player_size(Player *player) {
	if (!player) {
		return (Size) { .height = 0, .width = 0 };
	}

	return get_object_size(get_player_object(player));
}

/**
* Set the Player's direction.
*/
status set_player_direction(Player *player, int direction) {
	if (!player) {
		return STATUS_ERROR_SETVALUE;
	}

	if (!set_object_direction(get_player_object(player), direction)) {
		return STATUS_ERROR_SETVALUE;
	}

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Player's direction.
*/
int get_player_direction(Player *player) {
	if (!player) {
		return OBJECT_DIRECTION_DEFAULT;
	}

	return get_object_direction(get_player_object(player));
}

/**
* Set the Player's movement speed.
*/
status set_player_velocity(Player *player, unsigned int velocity) {
	if (!player) {
		return STATUS_ERROR_SETVALUE;
	}

	if (!set_object_velocity(get_player_object(player), velocity)) {
		return STATUS_ERROR_SETVALUE;
	}

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Player's movement speed.
*/
unsigned int get_player_velocity(Player *player) {
	if (!player) {
		return OBJECT_VELOCITY_DEFAULT;
	}

	return get_object_velocity(get_player_object(player));
}

/**
* Set the Player's Sprite.
*/
status set_player_sprite(Player *player, Sprite *sprite) {
	if (!player || !sprite) {
		return STATUS_ERROR_SETVALUE;
	}

	player->sprite = sprite;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Player's Sprite.
*/
Sprite *get_player_sprite(Player *player) {
	if (!player || !player->sprite) {
		return NULL;
	}

	return player->sprite;
}

/**
* Set the current animation frame index of the Player's sprite.
*/
status set_player_current_frame(Player *player, unsigned int current) {
	if (!player) {
		return STATUS_ERROR_SETVALUE;
	}

	set_sprite_current_frame(get_player_sprite(player), current);

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the current animation frame index of the Player's sprite.
*/
unsigned int get_player_current_frame(Player *player) {
	if (!player) {
		return SPRITE_FRAME_MAX_DEFAULT;
	}

	return get_sprite_current_frame(get_player_sprite(player));
}

/**
* Set the Player's HP (Hit Points / Lives).
*/
status set_player_hp(Player *player, unsigned int hp) {
	if (!player) {
		return STATUS_ERROR_SETVALUE;
	}

	player->hp = hp;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Player's HP (Hit Points / Lives).
*/
unsigned int get_player_hp(Player *player) {
	if (!player) {
		return PLAYER_HP_DEFAULT;
	}

	return player->hp;
}

/**
* Set the Player's score points.
*/
status set_player_score(Player *player, unsigned int score) {
	if (!player) {
		return STATUS_ERROR_SETVALUE;
	}

	player->score = score;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Player's score.
*/
unsigned int get_player_score(Player *player) {
	if (!player) {
		return PLAYER_SCORE_DEFAULT;
	}

	return player->score;
}

/**
 * Draw the Player's image with the specified animation frame on the screen.
 */
status draw_player(Player *player) {
	if (!player) {
		return STATUS_ERROR_SETVALUE;
	}

	Position player_position = get_player_position(player);

	al_draw_tinted_scaled_rotated_bitmap_region(
		get_sprite_image(get_player_sprite(player)),
		PLAYER_WIDTH * get_player_current_frame(player),
		0,
		PLAYER_WIDTH,
		PLAYER_HEIGHT,
		al_map_rgb(255, 255, 255),
		0,
		0,
		player_position.x,
		player_position.y,
		1,
		1,
		0,
		0
	);

	return STATUS_OK_SETVALUE;
}