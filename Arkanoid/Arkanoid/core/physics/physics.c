#include "./physics.h"
#include "./physics.h"

bool value_in_range(int value, int min, int max) {
	return (value >= min) && (value <= max);
}

bool objects_overlap(Object *object1, Object *object2) {
	Position object1_position = get_object_position(object1);
	Position object2_position = get_object_position(object2);
	Size object1_size = get_object_size(object1);
	Size object2_size = get_object_size(object2);

	bool x_overlap = value_in_range(object1_position.x, object2_position.x, object2_position.x + object2_size.width) ||
		value_in_range(object2_position.x, object1_position.x, object1_position.x + object1_size.width);

	bool y_overlap = value_in_range(object1_position.y, object2_position.y, object2_position.y + object2_size.height) ||
		value_in_range(object2_position.y, object1_position.y, object1_position.y + object1_size.height);

	return x_overlap && y_overlap;
}

status handle_physics_ball_bounds(Ball *ball) {
	Direction ball_direction = get_ball_direction(ball);
	Position ball_position = get_ball_position(ball);
	Size ball_size = get_ball_size(ball);

	if ((int)ball_position.x + 1 <= 0) {
		if (set_ball_direction(ball, -ball_direction.x, ball_direction.y) == STATUS_ERROR_SETVALUE) {
			return STATUS_ERROR_SETVALUE;
		}
	}

	if ((int)ball_position.y + 1 <= 0) {
		if (set_ball_direction(ball, ball_direction.x, -ball_direction.y) == STATUS_ERROR_SETVALUE) {
			return STATUS_ERROR_SETVALUE;
		}
	}

	if ((int)ball_position.x + 1 >= SCREEN_WIDTH - (int)ball_size.width) {
		if (set_ball_direction(ball, -ball_direction.x, ball_direction.y) == STATUS_ERROR_SETVALUE) {
			return STATUS_ERROR_SETVALUE;
		}
	}

	if ((int)ball_position.y + 1 >= SCREEN_HEIGHT - (int)ball_size.width) {
		if (set_ball_direction(ball, ball_direction.x, -ball_direction.y) == STATUS_ERROR_SETVALUE) {
			return STATUS_ERROR_SETVALUE;
		}
	}

	return STATUS_OK_SETVALUE;
}

status handle_physics_ball_block(Ball *ball, Block *block) {
	Direction ball_direction = get_ball_direction(ball);
	Position ball_position = get_ball_position(ball);
	Size ball_size = get_ball_size(ball);

	Position block_position = get_block_position(block);
	Size block_size = get_block_size(block);

	bool bottom_collision = ball_position.y <= block_position.y + block_size.height;
	bool top_collision = ball_position.y + ball_size.height >= block_position.y;
	bool left_collision = ball_position.x + ball_size.width <= block_position.x;
	bool right_collision = ball_position.x >= block_position.x + block_size.width;

	if (objects_overlap(get_ball_object(ball), get_block_object(block))) {
		if (bottom_collision) {
			set_ball_direction(ball, ball_direction.x, -ball_direction.y);
		}

		if (top_collision) {
			set_ball_direction(ball, ball_direction.x, -ball_direction.y);
		}

		if (right_collision) {
			set_ball_direction(ball, -ball_direction.x, ball_direction.y);
		}

		if (left_collision) {
			set_ball_direction(ball, -ball_direction.x, ball_direction.y);
		}
	}

	return STATUS_OK_SETVALUE;
}

status handle_physics_ball_player(Ball *ball, Player *player) {
	Direction ball_direction = get_ball_direction(ball);
	Position ball_position = get_ball_position(ball);
	Size ball_size = get_ball_size(ball);
	unsigned int ball_radius = ball_size.width;

	Position player_position = get_player_position(player);
	Size player_size = get_player_size(player);

	bool top_collision = (ball_position.y + ball_size.height >= player_position.y);

	bool left_collision = ball_position.x + ball_size.width <= player_position.x;
	bool right_collision = ball_position.x >= player_position.x + player_size.width;

	if (objects_overlap(get_ball_object(ball), get_block_object(player))) {
		if (top_collision) {
			set_ball_direction(ball, ball_direction.x, -ball_direction.y);
		}

		if (right_collision) {
			set_ball_direction(ball, -ball_direction.x, ball_direction.y);
		}

		if (left_collision) {
			set_ball_direction(ball, -ball_direction.x, ball_direction.y);
		}
	}

	return STATUS_OK_SETVALUE;
}