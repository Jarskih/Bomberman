#pragma once
#include <vector>
#include <SDL.h>
#include "Helpers.h"
#include "Block.h"
#include "player.h"

class Map
{
public:
	Map(int height, int width, SDL_Renderer* renderer) : m_size_Y(height), m_size_X(width), m_renderer(renderer) { generateMap(); };
	~Map() = default;
	void render();
	void loadTextures();
	std::vector<sp<Block>> tileSet = {};
private:
	int m_size_Y = 0;
	int m_size_X = 0;
	SDL_Renderer* m_renderer = nullptr;
	void generateMap();
	//std::string blockSprites[9] = { "img/block.png", "img/whiteBlock.png", "img/wallTop.png", "img/wallLeft.png", "img/wallRight.png", "img/wallDown.png", "img/wallTopLeft.png", "img/wallTopRight.png", "img/grass.png" };
};

