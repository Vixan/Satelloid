#include "./player.h"

/**
 * Create the Player with the specified game Object and Sprite properties
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
status draw_player(Player *player, unsigned int current_frame) {
	if (!player) {
		return STATUS_ERROR_SETVALUE;
	}

	Position player_position = get_object_position(get_player_object(player));

	al_draw_bitmap(
		get_sprite_image(get_player_sprite(player)),
		player_position.x, 
		player_position.y, 
		0
	);

	return STATUS_OK_SETVALUE;
}