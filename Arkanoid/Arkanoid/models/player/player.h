#pragma once

#include <stdlib.h>

#include "../object/object.h"
#include "../sprite/sprite.h"

typedef struct Player {
	Object *object;
	Sprite *sprite;
	unsigned int hp;
	unsigned int score;
} Player;

static const unsigned int PLAYER_HP_DEFAULT = 3;
static const unsigned int PLAYER_SCORE_DEFAULT = 0;
static const char *PLAYER_IMAGE_DEFAULT_PATH = "./assets/images/player/Satellite.png";
static const unsigned int PLAYER_HEIGHT = 64;
static const unsigned int PLAYER_WIDTH = 256;

Player *create_player(Object *object, Sprite *sprite, unsigned int hp, unsigned int score);
status destroy_player(Player *player);

status set_player_object(Player *player, Object *object);
Object *get_player_object(Player *player);

status set_player_sprite(Player *player, Sprite *sprite);
Sprite *get_player_sprite(Player *player);

status set_player_hp(Player *player, unsigned int hp);
unsigned int get_player_hp(Player *player);

status set_player_score(Player *player, unsigned int score);
unsigned int get_player_score(Player *player);

status draw_player(Player *player, unsigned int current_frame);