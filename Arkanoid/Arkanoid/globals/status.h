#pragma once

/**
 * Type to describe the codes returned by functions.
 */
typedef unsigned short status;

/**
 * Status codes that the functions will return.
 */
const enum Statuses {
	STATUS_OK_EXIT,
	STATUS_ERROR_EXIT,
	STATUS_OK_ALLEGRO,
	STATUS_ERROR_ALLEGRO,
	STATUS_ERROR_ALLEGRO_INIT,
	STATUS_ERROR_ALLEGRO_DISPLAY,
	STATUS_ERROR_ALLEGRO_EVENT_QUEUE,
	STATUS_ERROR_ALLEGRO_TIMER,
	STATUS_ERROR_ALLEGRO_FONT,
	STATUS_ERROR_ALLEGRO_COLOR,
	STATUS_ERROR_ALLEGRO_KEYBOARD,
	STATUS_ERROR_ALLEGRO_IMAGE,
	STATUS_ERROR_ALLEGRO_AUDIO,
	STATUS_ERROR_ALLEGRO_PRIMITIVES,
	STATUS_ERROR_FILE,
	STATUS_OK_SETVALUE,
	STATUS_ERROR_SETVALUE,
	STATUS_GAME_RUNNING,
	STATUS_GAME_OVER,
	STATUS_GAME_WON,
	STATUS_NEW_GAME,
	STATUS_GAME_NEXT_LEVEL
};