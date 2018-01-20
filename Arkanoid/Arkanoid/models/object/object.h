#pragma once

#include <stdlib.h>

#include "../../globals/status.h"

typedef struct Size {
	unsigned int height;
	unsigned int width;
} Size;

typedef struct Position {
	unsigned int x;
	unsigned int y;
} Position;

typedef struct Object {
	Position position;
	Size size;
	int direction;
	unsigned int velocity;
} Object;

static const int OBJECT_DIRECTION_DEFAULT = 0;
static const unsigned int OBJECT_VELOCITY_DEFAULT = 0;

Object *create_object(unsigned int x, unsigned int y, unsigned int height, unsigned int width, int direction, unsigned int velocity);
status destroy_object(Object *object);

status set_object_size(Object *object, unsigned int height, unsigned int width);
Size get_object_size(Object *object);

status set_object_position(Object *object, unsigned int x, unsigned int y);
Position get_object_position(Object *object);

status set_object_direction(Object *object, int direction);
int get_object_direction(Object *object);

status set_object_velocity(Object *object, unsigned int velocity);
unsigned int get_object_velocity(Object *object);