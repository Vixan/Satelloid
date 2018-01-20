#include "./object.h"

/**
 * Create and return a pointer to a game Object.
 */
Object *create_object(unsigned int x, unsigned int y, unsigned int height, unsigned int width, int direction, unsigned int velocity) {
	Object *object = malloc(sizeof(Object));

	object->position.x = x;
	object->position.y = y;
	object->size.height = height;
	object->size.width = width;
	object->direction = direction;
	object->velocity = velocity;

	return object;
}

/**
 * Set the size property of a game Object.
 */
void set_object_size(Object *object, unsigned int height, unsigned int width) {
	if (object) {
		object->size.height = height;
		object->size.width = width;
	}
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
void set_object_position(Object *object, unsigned int x, unsigned int y) {
	if (object) {
		object->position.x = x;
		object->position.y = y;
	}
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
void set_object_direction(Object *object, int direction) {
	if (object) {
		object->direction = direction;
	}
}

/**
* Retrieve the direction property of a game Object.
*/
int get_object_direction(Object *object) {
	return object->direction;
}

/**
* Set the velocity (speed) property of a game Object.
*/
void set_object_velocity(Object *object, unsigned int velocity) {
	if (object) {
		object->velocity = velocity;
	}
}

/**
* Retrieve the velocity (speed) property of a game Object.
*/
unsigned int get_object_velocity(Object *object) {
	return object->velocity;
}