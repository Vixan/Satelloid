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

typedef enum AllegroMessages {
	ALLEGRO_MESSAGE_ERROR,
	ALLEGRO_MESSAGE_INFO,
	ALLEGRO_MESSAGE_WARNING
} AllegroMessages;


static const char *ALLEGRO_COLOR_DARK = "#201a23"; // Raisin Black
static const char *ALLEGRO_COLOR_ERROR = "#ff1428"; // Rudy
static const char *ALLEGRO_COLOR_WARNING = "#ffe713"; // Vivid Yellow
static const char *ALLEGRO_COLOR_INFO = "#155ad4"; // Denim

static const char *ALLEGRO_COLOR_DEFAULT = "#ffffff"; // White
static const char *ALLEGRO_COLOR_TEXT = "#9e9e9e"; // Spanish Gray
static const char *ALLEGRO_COLOR_PRIMARY = "#41ead4"; // Turquoise
static const char *ALLEGRO_COLOR_SECONDARY = "#ff206e"; // Awesome
static const char *ALLEGRO_COLOR_TERNARY = "#5ed923"; // Harlequin Green
static const char *ALLEGRO_COLOR_ACCENT1 = "#ef003c"; // Red (Munsell)
static const char *ALLEGRO_COLOR_ACCENT2 = "#feda1e"; // Banana Yellow
static const char *ALLEGRO_COLOR_DARK_ALT = "#22084f"; // Middle Red Purple

static const float FPS = 60.0;
static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 720;
static const int WINDOW_MODE = ALLEGRO_WINDOWED;
static const char *ALLEGRO_FONT_FILE = "./assets/fonts/prime.otf";
static const int ALLEGRO_FONT_SIZE_HUGE = 72;
static const int ALLEGRO_FONT_SIZE_LARGE = 48;
static const int ALLEGRO_FONT_SIZE_NORMAL = 36;
static const int ALLEGRO_FONT_SIZE_SMALL = 24;
static const int ALLEGRO_SCALE_DEFAULT = 1;

Allegro *allegro_create();
status allegro_init(Allegro *allegro);
void allegro_destroy(Allegro *allegro);
void allegro_message(Allegro *allegro, AllegroMessages type, char *message);
void allegro_display_error(Allegro *allegro, status allegro_status);
void allegro_wait_keypress(ALLEGRO_EVENT_QUEUE *event_queue);