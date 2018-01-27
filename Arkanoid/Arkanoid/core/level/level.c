#include "./level.h"

/**
 * Retrieve the number of blocks from the passed matrix which reresents the level layout,
 */
int get_max_level_blocks(bool level[ROWS][COLS]) {
	int blocks_max = 0;

	if (!level[0][0]) {
		return 0;
	}

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (level[i][j]) {
				blocks_max++;
			}
		}
	}

	return blocks_max;
}

/**
 * Create the level layout (blocks layout) of the game.
 */
Block **create_level(bool level[ROWS][COLS], unsigned int blocks_max) {
	Block **blocks = malloc(sizeof(Block *) * blocks_max);

	for (int i = 0; i < (int)blocks_max; i++) {
		blocks[i] = create_block(
			create_object(
				0,
				0,
				BLOCK_HEIGHT,
				BLOCK_WIDTH,
				0,
				0,
				OBJECT_VELOCITY_DEFAULT
			),
			create_sprite(
			(char *)BLOCK_IMAGE_DEFAULT_PATH,
				(unsigned int)SPRITE_FRAME_MIN_DEFAULT,
				(unsigned int)SPRITE_FRAME_MAX_DEFAULT,
				(unsigned int)SPRITE_FRAME_CURRENT_DEFAULT
			),
			BLOCK_HP_DEFAULT
		);
	}

	for (int q = 0; q < (int)blocks_max; ) {
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				if (level[i][j]) {
					set_block_position(
						blocks[q],
						BLOCK_WIDTH * j + j * BLOCK_GAP + BLOCK_GAP / 2,
						BLOCK_HEIGHT * i + i * BLOCK_GAP + BLOCK_GAP);
					q++;
				}
			}
		}
	}

	return blocks;
}
