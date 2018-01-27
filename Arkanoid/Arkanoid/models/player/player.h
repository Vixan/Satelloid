#pragma once
#pragma warning(disable : 4996)

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include "../../core/allegro/allegro.h"
#include "../../globals/game.h"
#include "../../globals/status.h"
#include "../object/object.h"
#include "../sprite/sprite.h"

typedef struct Player {
	Object *object;
	Sprite *sprite;
	unsigned int hp;
	unsigned int score;
} Player;

static const unsigned int PLAYER_HP_DEFAULT = 3;
static const unsigned int PLAYER_VELOCITY_DEFAULT = 8;
static const unsigned int PLAYER_SCORE_DEFAULT = 0;
static const char *PLAYER_IMAGE_DEFAULT_PATH = "./assets/images/player/satellite.png";
static const char *PLAYER_HP_IMAGE_PATH = "./assets/images/misc/bolt.png";
static const unsigned int PLAYER_HEIGHT = 64;
static const unsigned int PLAYER_WIDTH = 256;
static const unsigned int PLAYER_SPRITE_MAX = 2;

Player *create_player(Object *object, Sprite *sprite, unsigned int hp, unsigned int score);
status destroy_player(Player *player);

status set_player_object(Player *player, Object *object);
Object *get_player_object(Player *player);

status set_player_position(Player *player, unsigned int x, unsigned int y);
Position get_player_position(Player *player);

status set_player_size(Player *player, unsigned int height, unsigned int width);
Size get_player_size(Player *player);

status set_player_direction(Player *player, int x, int y);
Direction get_player_direction(Player *player);

status set_player_velocity(Player *player, int velocity);
int get_player_velocity(Player *player);

status set_player_sprite(Player *player, Sprite *sprite);
Sprite *get_player_sprite(Player *player);

status set_player_current_frame(Player *player, unsigned int current);
unsigned int get_player_current_frame(Player *player);

status set_player_hp(Player *player, unsigned int hp);
unsigned int get_player_hp(Player *player);

status set_player_score(Player *player, unsigned int score);
unsigned int get_player_score(Player *player);

status draw_player(Player *player);
status show_player_score(Allegro *allegro, Player *player, ALLEGRO_FONT *score_font);
status show_player_hp(ALLEGRO_BITMAP *image, Player *player, int image_size);