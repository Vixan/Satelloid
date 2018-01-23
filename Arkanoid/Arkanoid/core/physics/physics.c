#include "./physics.h"
#include "./physics.h"

status handle_physics_ball_bounds(Ball *ball) {
	Direction ball_direction = get_ball_direction(ball);
	Position ball_position = get_ball_position(ball);
	Size ball_size = get_ball_size(ball);

	if ((int)ball_position.x >= SCREEN_WIDTH - ball_size.width) {
		if (set_ball_direction(ball, -ball_direction.x, ball_direction.y) == STATUS_ERROR_SETVALUE) {
			return STATUS_ERROR_SETVALUE;
		}
	}

	if ((int)ball_position.y >= SCREEN_HEIGHT - ball_size.height) {
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

	bool right_collision = ball_position.x >= block_position.x + block_size.width;
	bool bottom_collision = ball_position.y >= block_position.y + block_size.height;
	bool left_collision = block_position.x >= ball_position.x + ball_size.width;
	bool top_collision = block_position.y >= ball_position.y + ball_size.height;

	if (!(right_collision || bottom_collision || left_collision || top_collision)) {
		if (!right_collision) {
			set_ball_direction(ball, ball_direction.x + BLOCK_COLLISION_VELOCITY_RATE_DEFAULT, -ball_direction.y);
		}
		if (!left_collision) {
			set_ball_direction(ball, ball_direction.x - BLOCK_COLLISION_VELOCITY_RATE_DEFAULT, -ball_direction.y);
		}
		if (!top_collision) {
			set_ball_direction(ball, ball_direction.x, -ball_direction.y);
		}
		if (!bottom_collision) {
			set_ball_direction(ball, -ball_direction.x, ball_direction.y);
		}
	}

	return STATUS_OK_SETVALUE;
}

status handle_physics_ball_player(Ball *ball, Player *player) {
	Direction ball_direction = get_ball_direction(ball);
	Position ball_position = get_ball_position(ball);
	Size ball_size = get_ball_size(ball);

	Position player_position = get_player_position(player);
	Size player_size = get_player_size(player);

	bool right_collision = ball_position.x >= player_position.x + player_size.width;
	bool bottom_collision = ball_position.y >= player_position.y + player_size.height;
	bool left_collision = player_position.x >= ball_position.x + ball_size.width;
	bool top_collision = player_position.y >= ball_position.y + ball_size.height;

	if (!(right_collision || bottom_collision || left_collision || top_collision)) {
		if (!bottom_collision) {
			set_ball_direction(ball, ball_direction.x, -ball_direction.y);
		}
	}
}