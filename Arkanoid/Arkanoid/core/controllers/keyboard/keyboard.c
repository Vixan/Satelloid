#include "./keyboard.h"

status handle_player_movement(Allegro *allegro, bool keys[], Player *player) {
	Position player_position = get_player_position(player);
	Size player_size = get_player_size(player);
	unsigned int player_velocity = get_player_velocity(player);
	unsigned int frame_delay = 8;
	unsigned int frame_max = get_sprite_max_frame(get_player_sprite(player));

	if (keys[KEY_UP]) {}
	if (keys[KEY_DOWN]) {}

	if (keys[KEY_LEFT] && player_position.x >= player_velocity) {
		set_sprite_frame_column(get_player_sprite(player), 2);
		set_player_direction(player, -1, get_player_direction(player).y);

		if (!set_player_position(player, player_position.x - player_velocity, player_position.y)) {
			return STATUS_ERROR_SETVALUE;
		}
	}
	else if (keys[KEY_RIGHT] && player_position.x <= SCREEN_WIDTH - player_size.width - player_velocity) {
		set_sprite_frame_column(get_player_sprite(player), 1);
		set_player_direction(player, 1, get_player_direction(player).y);

		if (!set_player_position(player, player_position.x + player_velocity, player_position.y)) {
			return STATUS_ERROR_SETVALUE;
		}
	}
	else {
		set_sprite_frame_column(get_player_sprite(player), SPRITE_FRAME_COLUMN_DEFAULT);
		set_player_direction(player, 0, 0);
	}

	if (set_sprite_frame_count(get_player_sprite(player), get_sprite_frame_count(get_player_sprite(player)) + 1) == STATUS_ERROR_SETVALUE) {
		return STATUS_ERROR_SETVALUE;
	}

	if (get_sprite_frame_count(get_player_sprite(player)) >= frame_delay) {
		set_player_current_frame(player, get_player_current_frame(player) + 1);
		if (get_player_current_frame(player) >= frame_max) {
			set_player_current_frame(player, frame_max - 1);
		}

		set_sprite_frame_count(get_player_sprite(player), SPRITE_FRAME_CURRENT_DEFAULT);
	}

	return STATUS_OK_SETVALUE;
}

status handle_keyboard(Allegro *allegro, bool keys[], ALLEGRO_EVENT event, Player *player) {
	if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
		keys[KEY_LEFT] = false;
		keys[KEY_RIGHT] = false;

		switch (event.keyboard.keycode) {
		case ALLEGRO_KEY_UP:
			keys[KEY_UP] = true;
			break;

		case ALLEGRO_KEY_DOWN:
			keys[KEY_DOWN] = true;
			break;

		case ALLEGRO_KEY_LEFT:
			keys[KEY_LEFT] = true;
			set_sprite_frame_column(get_player_sprite(player), 2);
			break;

		case ALLEGRO_KEY_RIGHT:
			keys[KEY_RIGHT] = true;
			set_sprite_frame_column(get_player_sprite(player), 1);
			break;
		}
	}
	else if (event.type == ALLEGRO_EVENT_KEY_UP) {
		switch (event.keyboard.keycode) {
		case ALLEGRO_KEY_UP:
			keys[KEY_UP] = false;
			break;

		case ALLEGRO_KEY_DOWN:
			keys[KEY_DOWN] = false;
			break;

		case ALLEGRO_KEY_LEFT:
			keys[KEY_LEFT] = false;
			break;

		case ALLEGRO_KEY_RIGHT:
			keys[KEY_RIGHT] = false;
			break;

		case ALLEGRO_KEY_ESCAPE:
			return STATUS_OK_EXIT;
		}
	}

	return STATUS_OK_SETVALUE;
}