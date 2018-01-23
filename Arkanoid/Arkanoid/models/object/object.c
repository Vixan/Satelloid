#include "./object.h"

/**
 * Create a game Object.
 */
Object *create_object(unsigned int x, unsigned int y, unsigned int height, unsigned int width,
	int dx, int dy, int velocity) {
	Object *object = malloc(sizeof(Object));
	if (!object) {
		return NULL;
	}

	object->position.x = x;
	object->position.y = y;
	object->size.height = height;
	object->size.width = width;
	object->direction.x = dx;
	object->direction.y = dy;
	object->velocity = velocity;

	return object;
}

/**
 * Destroy the game Object and free up the memory used.
 */
status destroy_object(Object *object) {
	if (!object) {
		return STATUS_ERROR_SETVALUE;
	}

	free(object);

	return STATUS_OK_SETVALUE;
}

/**
 * Set the size property of a game Object.
 */
status set_object_size(Object *object, unsigned int height, unsigned int width) {
	if (!object) {
		return STATUS_ERROR_SETVALUE;
	}
	object->size.height = height;
	object->size.width = width;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the size property of a game Object.
*/
Size get_object_size(Object *object) {
	return object->size;
}

/**
* Set the position property of a game Object.
*/
status set_object_position(Object *object, unsigned int x, unsigned int y) {
	if (!object) {
		return STATUS_ERROR_SETVALUE;
	}
	object->position.x = x;
	object->position.y = y;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the position property of a game Object.
*/
Position get_object_position(Object *object) {
	return object->position;
}

/**
* Set the direction property of a game Object.
*/
status set_object_direction(Object *object, int x, int y) {
	if (!object) {
		return STATUS_ERROR_SETVALUE;
	}
	object->direction.x = x;
	object->direction.y = y;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the direction property of a game Object.
*/
Direction get_object_direction(Object *object) {
	if (!object) {
		return (Direction) { .x = 0, .y = 0 };
	}

	return object->direction;
}

/**
* Set the velocity (speed) property of a game Object.
*/
status set_object_velocity(Object *object, int velocity) {
	if (!object) {
		return STATUS_ERROR_SETVALUE;
	}
	object->velocity = velocity;

	return STATUS_OK_SETVALUE;
}

/**
* Retrieve the velocity (speed) property of a game Object.
*/
int get_object_velocity(Object *object) {
	return object->velocity;
}