#pragma once
#include <SDL.h>
#include "GameRules.h"
#include <utility>

class Block
{
public:
	Block(int x, int y, int blockType) : posX(x), posY(y), blockType(blockType) {};
	~Block() = default;

	int blockType;
	SDL_Rect collider = { 0,0, BLOCK_WIDTH, BLOCK_HEIGHT };
	SDL_Texture* LoadTexture(SDL_Renderer* renderer);
	void changeBlockType(int newType);
	std::pair <int, int> getBlockIndex();
	void render(SDL_Renderer* renderer);
private:
	int posX;
	int posY;
	bool isDestroyed = false;
	bool destroyedTextureLoaded = false;
	bool textureLoaded = false;
	SDL_Rect windowRect = { 0, 0, BLOCK_WIDTH, BLOCK_HEIGHT };
	SDL_Rect textureRect = { 0, 0, 0, 0 };
	const char* m_sprite = nullptr;
	SDL_Texture* texture = nullptr;

	void GetSprite();
};

