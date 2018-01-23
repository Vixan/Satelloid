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

typedef struct Direction {
	int x;
	int y;
} Direction;

typedef struct Object {
	Position position;
	Size size;
	Direction direction;
	int velocity;
} Object;

static const int OBJECT_VELOCITY_DEFAULT = 0;

Object *create_object(unsigned int x, unsigned int y, unsigned int height, unsigned int width, int dx, int dy, int velocity);
status destroy_object(Object *object);

status set_object_size(Object *object, unsigned int height, unsigned int width);
Size get_object_size(Object *object);

status set_object_position(Object *object, unsigned int x, unsigned int y);
Position get_object_position(Object *object);

status set_object_direction(Object *object, int x, int y);
Direction get_object_direction(Object *object);

status set_object_velocity(Object *object, int velocity);
int get_object_velocity(Object *object);