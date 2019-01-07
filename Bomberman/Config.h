#pragma once
namespace Config {
	//Game area
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

	// Blocks
	static const int MAX_BLOCKS_X = 15;
	static const int MAX_BLOCKS_Y = 14;
	static const int BLOCK_WIDTH = SCREEN_WIDTH / MAX_BLOCKS_X;
	static const int BLOCK_HEIGHT = SCREEN_HEIGHT / MAX_BLOCKS_Y;
	static const int BLOCK_OFFSET_X = BLOCK_WIDTH / 2;
	static const int BLOCK_OFFSET_Y = BLOCK_HEIGHT / 2;

	// Player
	static const int PLAYER_WIDTH = BLOCK_WIDTH * 2;
	static const int PLAYER_HEIGHT = BLOCK_HEIGHT * 1.5;

	static const int NUMBER_OF_PLAYERS = 1;
	static const int STARTING_LIVES = 2;
	static const int ROUND_TIME = 240;

	// Enemies
	static const int NUMBER_OF_ENEMIES = 3;

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
}

// MAP LAYOUT [Y,X]
/*
static const int MAP_LAYOUT[14][15] = {
	// 0: { NONBREAKABLE, NONBREAKABLE, NONBREAKABLE, NONBREAKABLE, NONBREAKABLE, NONBREAKABLE, NONBREAKABLE, NONBREAKABLE, NONBREAKABLE, NONBREAKABLE, NONBREAKABLE, NONBREAKABLE, NONBREAKABLE, NONBREAKABLE, NONBREAKABLE },
	/* 1: { WALL_LEFT_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_UP, WALL_RIGHT_UP },
	/* 2: { WALL_LEFT, GRASS, GRASS, BREAKABLE, GRASS, BREAKABLE, BREAKABLE, GRASS, GRASS, BREAKABLE, BREAKABLE, GRASS, GRASS, GRASS, WALL_RIGHT },
	/* 3: { WALL_LEFT, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, BREAKABLE, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, WALL_RIGHT },
	/* 4: { WALL_LEFT, GRASS, BREAKABLE, GRASS, GRASS, BREAKABLE, GRASS, GRASS, GRASS, BREAKABLE, GRASS, BREAKABLE, BREAKABLE, GRASS, WALL_RIGHT },
	/* 5: { WALL_LEFT, BREAKABLE, NONBREAKABLE, BREAKABLE, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, BREAKABLE, NONBREAKABLE, GRASS, WALL_RIGHT },
	/* 6: { WALL_LEFT, GRASS, BREAKABLE, GRASS, GRASS, BREAKABLE, GRASS, BREAKABLE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, WALL_RIGHT },
	/* 7: { WALL_LEFT, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, BREAKABLE, NONBREAKABLE, GRASS, NONBREAKABLE, BREAKABLE, NONBREAKABLE, GRASS, NONBREAKABLE, BREAKABLE, WALL_RIGHT },
	/* 8: { WALL_LEFT, BREAKABLE, GRASS, GRASS, GRASS, GRASS, BREAKABLE, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, WALL_RIGHT },
	/* 9: { WALL_LEFT, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, BREAKABLE, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, WALL_RIGHT },
	/* 10:{ WALL_LEFT, GRASS, GRASS, GRASS, BREAKABLE, GRASS, BREAKABLE, GRASS, GRASS, GRASS, GRASS, GRASS, BREAKABLE, GRASS, WALL_RIGHT },
	/* 11:{ WALL_LEFT, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, BREAKABLE, NONBREAKABLE, BREAKABLE, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, NONBREAKABLE, GRASS, WALL_RIGHT },
	/* 12:{ WALL_LEFT, GRASS, GRASS, GRASS, BREAKABLE, BREAKABLE, GRASS, GRASS, GRASS, GRASS, GRASS, BREAKABLE, BREAKABLE,GRASS, WALL_RIGHT },
	/* 13:{ WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN, WALL_DOWN }
};
*/