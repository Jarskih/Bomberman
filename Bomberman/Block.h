#pragma once
#include <SDL.h>
#include "GameRules.h"

class Block
{
public:
	Block(int x, int y, int blockType) : m_x(x), m_y(y), m_blockType(blockType) {};
	~Block() = default;
	SDL_Texture* LoadTexture(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
private:
	enum Blocks { BREAKABLE, NONBREAKABLE, WALL_UP, WALL_LEFT, WALL_RIGHT, WALL_DOWN, WALL_LEFT_UP, WALL_RIGHT_UP, WALL_LEFT_DOWN, WALL_RIGHT_DOWN, GRASS, DESTROYED };
	int m_x;
	int m_y;
	int m_blockType;
	bool isDestroyed = false;
	bool destroyedTextureLoaded = false;
	bool textureLoaded = false;
	SDL_Rect windowRect = { 0, 0, BLOCK_WIDTH, BLOCK_HEIGHT };
	const char* m_sprite = nullptr;
	SDL_Texture* texture = nullptr;
	void GetSprite();
};

