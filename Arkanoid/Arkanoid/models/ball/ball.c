#include "./ball.h"

/**
* Create a Ball with the specified game Object and Sprite properties.
*/
Ball *create_ball(Object *object, Sprite *sprite, unsigned int type) {
	Ball *ball = malloc(sizeof(Ball));
	if (!ball || !object || !sprite) {
		return NULL;
	}

	ball->object = object;
	ball->sprite = sprite;
	ball->type = type;

	return ball;
}

/**
* Destroy the Ball and free up the memory used.
*/
status destroy_ball(Ball *ball) {
	if (!ball) {
		return STATUS_ERROR_SETVALUE;
	}

	free(ball->object);
	al_destroy_bitmap(ball->sprite->image);
	free(ball->sprite);
	free(ball);

	return STATUS_OK_SETVALUE;
}

/**
* Set the Ball's game Object properties.
*/
status set_ball_object(Ball *ball, Object *object) {
	if (!ball || !object) {
		return STATUS_ERROR_SETVALUE;
	}

	ball->object = object;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Ball's game Object.
*/
Object *get_ball_object(Ball *ball) {
	if (!ball || !ball->object) {
		return NULL;
	}

	return ball->object;
}

/**
* Set the Ball's position in X and Y coordinates.
*/
status set_ball_position(Ball *ball, unsigned int x, unsigned int y) {
	if (!ball) {
		return STATUS_ERROR_SETVALUE;
	}

	if (!set_object_position(get_ball_object(ball), x, y)) {
		return STATUS_ERROR_SETVALUE;
	}

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Ball's position in X and Y coordinates.
*/
Position get_ball_position(Ball *ball) {
	if (!ball) {
		return (Position) { .x = 0, .y = 0 };
	}

	return get_object_position(get_ball_object(ball));
}

/**
* Set the Ball's height and width.
*/
status set_ball_size(Ball *ball, unsigned int height, unsigned int width) {
	if (!ball) {
		return STATUS_ERROR_SETVALUE;
	}

	if (!set_object_size(get_ball_object(ball), height, width)) {
		return STATUS_ERROR_SETVALUE;
	}

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Ball's height and width.
*/
Size get_ball_size(Ball *ball) {
	if (!ball) {
		return (Size) { .height = 0, .width = 0 };
	}

	return get_object_size(get_ball_object(ball));
}

/**
* Set the Ball's direction.
*/
status set_ball_direction(Ball *ball, int x, int y) {
	if (!ball) {
		return STATUS_ERROR_SETVALUE;
	}

	if (!set_object_direction(get_ball_object(ball), x, y)) {
		return STATUS_ERROR_SETVALUE;
	}

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Ball's direction.
*/
Direction get_ball_direction(Ball *ball) {
	if (!ball) {
		return (Direction) { .x = 0, .y = 0 };
	}

	return get_object_direction(get_ball_object(ball));
}

/**
* Set the Ball's movement speed.
*/
status set_ball_velocity(Ball *ball, int velocity) {
	if (!ball) {
		return STATUS_ERROR_SETVALUE;
	}
	if (velocity < 0) {
		velocity = BALL_VELOCITY_MIN;
	}

	if (!set_object_velocity(get_ball_object(ball), velocity)) {
		return STATUS_ERROR_SETVALUE;
	}

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Ball's movement speed.
*/
int get_ball_velocity(Ball *ball) {
	if (!ball) {
		return OBJECT_VELOCITY_DEFAULT;
	}

	return get_object_velocity(get_ball_object(ball));
}

/**
* Set the Ball's Sprite.
*/
status set_ball_sprite(Ball *ball, Sprite *sprite) {
	if (!ball || !sprite) {
		return STATUS_ERROR_SETVALUE;
	}

	ball->sprite = sprite;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Ball's Sprite.
*/
Sprite *get_ball_sprite(Ball *ball) {
	if (!ball || !ball->sprite) {
		return NULL;
	}

	return ball->sprite;
}

/**
* Set the current animation frame index of the Ball's sprite.
*/
status set_ball_current_frame(Ball *ball, unsigned int current) {
	if (!ball) {
		return STATUS_ERROR_SETVALUE;
	}

	set_sprite_current_frame(get_ball_sprite(ball), current);

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the current animation frame index of the Ball's sprite.
*/
unsigned int get_ball_current_frame(Ball *ball) {
	if (!ball) {
		return SPRITE_FRAME_MAX_DEFAULT;
	}

	return get_sprite_current_frame(get_ball_sprite(ball));
}

/**
* Set the Ball's type.
*/
status set_ball_type(Ball *ball, unsigned int type) {
	if (!ball) {
		return STATUS_ERROR_SETVALUE;
	}

	ball->type = type;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the Ball's type.
*/
unsigned int get_ball_type(Ball *ball) {
	if (!ball) {
		return BALL_TYPE_DEFAULT;
	}

	return ball->type;
}

/**
* Draw the Ball's image with the specified animation frame on the screen.
*/
status draw_ball(Ball *ball) {
	if (!ball) {
		return STATUS_ERROR_SETVALUE;
	}

	Position ball_position = get_object_position(get_ball_object(ball));

	al_draw_tinted_scaled_rotated_bitmap_region(
		get_sprite_image(get_ball_sprite(ball)),
		BALL_WIDTH * get_ball_current_frame(ball),
		0,
		BALL_WIDTH,
		BALL_HEIGHT,
		al_map_rgb(255, 255, 255),
		0,
		0,
		ball_position.x,
		ball_position.y,
		1,
		1,
		0,
		0
	);

	return STATUS_OK_SETVALUE;
}