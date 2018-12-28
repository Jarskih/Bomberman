#pragma once
//Gamearea: x = 15 blocks, y = 13 blocks
static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 800;

// BLOCKS
static const int BLOCK_WIDTH = SCREEN_WIDTH / 15;
static const int BLOCK_HEIGHT = (SCREEN_HEIGHT) / 14;
static const int BLOCK_OFFSET_X = BLOCK_WIDTH / 2;
static const int BLOCK_OFFSET_Y = BLOCK_HEIGHT / 2;

// PLAYER
static const int PLAYER_WIDTH = BLOCK_WIDTH * 2;
static const int PLAYER_HEIGHT = BLOCK_HEIGHT * 1.5;

enum Blocks
{
	BREAKABLE,
	NONBREAKABLE,
	WALL_UP,
	WALL_LEFT,
	WALL_RIGHT,
	WALL_DOWN,
	WALL_LEFT_UP,
	WALL_RIGHT_UP,
	WALL_LEFT_DOWN,
	WALL_RIGHT_DOWN,
	GRASS,
	DESTROYED
};

// MAP LAYOUT [Y,X]
static const int MAP_LAYOUT[14][15] = {
	/* 0: */{ WALL_LEFT_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_RIGHT_UP },
	/* 1: */{ WALL_LEFT_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_RIGHT_UP },
	/* 2: */{ WALL_LEFT, GRASS, GRASS, BREAKABLE, GRASS, BREAKABLE, BREAKABLE, GRASS, GRASS, BREAKABLE, BREAKABLE, GRASS, GRASS, GRASS, WALL_RIGHT },
	/* 3: */{ WALL_LEFT, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, BREAKABLE, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, WALL_RIGHT },
	/* 4: */{ WALL_LEFT, GRASS, BREAKABLE, GRASS, GRASS, BREAKABLE, GRASS, GRASS, GRASS, BREAKABLE, GRASS, BREAKABLE, BREAKABLE, GRASS, WALL_RIGHT },
	/* 5: */{ WALL_LEFT, BREAKABLE, NONBREAKABLE, BREAKABLE, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, BREAKABLE, NONBREAKABLE, GRASS, WALL_RIGHT },
	/* 6: */{ WALL_LEFT, GRASS, BREAKABLE, GRASS, GRASS, BREAKABLE, GRASS, BREAKABLE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, WALL_RIGHT },
	/* 7: */{ WALL_LEFT, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, BREAKABLE, NONBREAKABLE, GRASS, NONBREAKABLE, BREAKABLE, NONBREAKABLE, GRASS, NONBREAKABLE, BREAKABLE, WALL_RIGHT },
	/* 8: */{ WALL_LEFT, BREAKABLE, GRASS, GRASS, GRASS, GRASS, BREAKABLE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, WALL_RIGHT },
	/* 9: */{ WALL_LEFT, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, BREAKABLE, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, WALL_RIGHT },
	/* 10:*/{ WALL_LEFT, GRASS, GRASS, GRASS, BREAKABLE, GRASS, BREAKABLE, GRASS, GRASS, GRASS, GRASS, GRASS, BREAKABLE, GRASS, WALL_RIGHT },
	/* 11:*/{ WALL_LEFT, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, BREAKABLE, NONBREAKABLE, BREAKABLE, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, WALL_RIGHT },
	/* 12:*/{ WALL_LEFT, GRASS, GRASS, GRASS, BREAKABLE, BREAKABLE, GRASS, GRASS, GRASS, GRASS, GRASS, BREAKABLE, BREAKABLE,GRASS, WALL_RIGHT },
	/* 13:*/{ WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN }
};
