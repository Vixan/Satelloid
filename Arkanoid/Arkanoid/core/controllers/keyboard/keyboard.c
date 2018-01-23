#include "./keyboard.h"

status handle_player_movement(Allegro *allegro, bool keys[], Player *player) {
	Position player_position = get_object_position(get_player_object(player));

	if (keys[KEY_UP]) {}
	if (keys[KEY_DOWN]) {}

	if (keys[KEY_LEFT] && player_position.x >= 4.0) {
		if (!set_object_position(get_player_object(player), player_position.x - 4, player_position.y)) {
			return STATUS_ERROR_SETVALUE;
		}
	}

	if (keys[KEY_RIGHT] && player_position.x <= SCREEN_WIDTH - get_object_size(get_player_object(player)).width - 4.0) {
		if (!set_object_position(get_player_object(player), player_position.x - 4, player_position.y)) {
			set_object_position(get_player_object(player), player_position.x + 4, player_position.y);
		}
	}

	return STATUS_OK_SETVALUE;
}

status handle_keyboard(Allegro *allegro, bool keys[], ALLEGRO_EVENT event, Player *player, Ball *ball, Block *block) {
	draw_player(player, SPRITE_FRAME_MIN_DEFAULT);
	draw_ball(ball, SPRITE_FRAME_MIN_DEFAULT);
	draw_block(block, SPRITE_FRAME_MIN_DEFAULT);
	al_flip_display();
	al_clear_to_color(al_color_html(ALLEGRO_COLOR_DARK));

	al_wait_for_event(allegro->event_queue, &event);

	if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (event.keyboard.keycode) {
		case ALLEGRO_KEY_UP:
			keys[KEY_UP] = true;
			break;

		case ALLEGRO_KEY_DOWN:
			keys[KEY_DOWN] = true;
			break;

		case ALLEGRO_KEY_LEFT:
			keys[KEY_LEFT] = true;
			break;

		case ALLEGRO_KEY_RIGHT:
			keys[KEY_RIGHT] = true;
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
	if (event.type == ALLEGRO_EVENT_TIMER) {
		Position player_position = get_object_position(get_player_object(player));

		if (keys[KEY_UP]) {}
		if (keys[KEY_DOWN]) {}

		if (keys[KEY_LEFT] && player_position.x >= 4.0) {
			if (!set_object_position(get_player_object(player), player_position.x - get_object_velocity(get_player_object(player)), player_position.y)) {
				return STATUS_ERROR_SETVALUE;
			}
		}

		if (keys[KEY_RIGHT] && player_position.x <= SCREEN_WIDTH - get_object_size(get_player_object(player)).width - 4.0) {
			if (!set_object_position(get_player_object(player), player_position.x + get_object_velocity(get_player_object(player)), player_position.y)) {
				return STATUS_ERROR_SETVALUE;
			}
		}
	}
	if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		return STATUS_OK_EXIT;
	}

	return STATUS_OK_SETVALUE;
}