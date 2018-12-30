#pragma once
#include <SDL.h>
#include "GameRules.h"
#include <utility>
#include "Flame.h"

class Block
{
public:
	Block(int x, int y, int blockType) : m_pos_x(x), m_pos_y(y), blockType(blockType)
	{
		index_x = Helpers::getCurrentBlock(m_pos_x, m_pos_y).first;
		index_y = Helpers::getCurrentBlock(m_pos_x, m_pos_y).second;
	};
	~Block() = default;

	SDL_Rect collider = { 0,0, BLOCK_WIDTH, BLOCK_HEIGHT };
	SDL_Texture* LoadTexture(SDL_Renderer* renderer);
	void changeBlockType(int newType);
	std::pair <int, int> getBlockIndex();
	void render(SDL_Renderer* renderer);
	int index_x;
	int index_y;
	int m_pos_x;
	int m_pos_y;
	int blockType;
	bool blockHasPowerUp = false;
	int powerUpType = 0;
private:
	Uint32 timeExploded = 0;
	Uint32 currentTime = 0;
	int frame = 0;
	bool isDestroyed = false;
	bool destroyedTextureLoaded = false;
	bool textureLoaded = false;
	SDL_Rect windowRect = { 0, 0, BLOCK_WIDTH, BLOCK_HEIGHT };
	SDL_Rect textureRect = { 0, 0, 0, 0 };
	const char* m_sprite = nullptr;
	SDL_Texture* m_texture = nullptr;
	bool powerUpAdded = false;

	void GetSprite();
};

