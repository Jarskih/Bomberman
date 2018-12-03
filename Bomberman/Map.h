#pragma once
#include <vector>
#include <SDL.h>
#include "GameRules.h"
#include "Helpers.h"
#include "Block.h"

class Map
{
public:
	Map(int height, int width) : size_Y(height), size_X(width) { generateMap(); };
	~Map() = default;
	void render(SDL_Renderer* renderer);
	void loadTextures(SDL_Renderer * renderer);
	std::vector<sp<Block>> m_tileSet = {};
private:
	enum Blocks { BREAKABLE, NONBREAKABLE, WALL_UP, WALL_LEFT, WALL_RIGHT, WALL_DOWN, WALL_LEFT_UP, WALL_RIGHT_UP, WALL_LEFT_DOWN, WALL_RIGHT_DOWN, GRASS };
	int size_Y = 0;
	int size_X = 0;
	void generateMap();
	//std::string blockSprites[9] = { "img/block.png", "img/whiteBlock.png", "img/wallTop.png", "img/wallLeft.png", "img/wallRight.png", "img/wallDown.png", "img/wallTopLeft.png", "img/wallTopRight.png", "img/grass.png" };
	int blockTypes[13][15] = {
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
};


