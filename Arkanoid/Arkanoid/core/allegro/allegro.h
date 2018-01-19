#pragma once

#include <stdarg.h>
#include <string.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_color.h>

#include "../../globals/status.h"

/**
 * Config structure to group the used Allegro 5 properties and addons.
 */
typedef struct Allegro {
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font;
} Allegro;

const enum ControlKeys {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

typedef enum AllegroMessages {
	ALLEGRO_MESSAGE_ERROR,
	ALLEGRO_MESSAGE_INFO,
	ALLEGRO_MESSAGE_WARNING
} AllegroMessages;
static const char *ALLEGRO_COLOR_DARK = "#201a23"; // Raisin Black
static const char *ALLEGRO_COLOR_ERROR = "#ff1428"; // Rudy
static const char *ALLEGRO_COLOR_WARNING = "#ffe713"; // Vivid Yellow
static const char *ALLEGRO_COLOR_INFO = "#155ad4"; // Denim

static const float FPS = 60.0;
static const int SCREEN_WIDTH = 1024;
static const int SCREEN_HEIGHT = 768;
static const int WINDOW_MODE = ALLEGRO_NOFRAME;
static const char *ALLEGRO_FONT_FILE = "./assets/fonts/pixelar.ttf";
static const int ALLEGRO_FONT_DEFAULT_SIZE = 16;

Allegro *allegro_create();
status allegro_init(Allegro *allegro);
void allegro_destroy(Allegro *allegro);
void allegro_message(Allegro *allegro, AllegroMessages type, char *message);
void allegro_wait_keypress(ALLEGRO_EVENT_QUEUE *event_queue);