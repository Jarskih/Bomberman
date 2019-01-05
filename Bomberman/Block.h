#pragma once
#include <SDL.h>
#include "GameRules.h"
#include <utility>
#include "Textures.h"
#include "Service.h"

class Block
{
public:
	Block(int x, int y, int blockType) : m_pos_x(x), m_pos_y(y), blockType(blockType)
	{
		index_x = Helpers::getCurrentBlock(m_pos_x, m_pos_y).first;
		index_y = Helpers::getCurrentBlock(m_pos_x, m_pos_y).second;
		m_textures = Service<Textures>::Get();
		oldblockType = blockType;
		LoadTexture();
	};
	~Block() = default;

	SDL_Rect collider = { 0,0, BLOCK_WIDTH, BLOCK_HEIGHT };
	void LoadTexture();
	void changeBlockType(int newType);
	std::pair <int, int> getBlockIndex() const;
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
	int frame = 0;
	bool textureLoaded = false;
	int oldblockType;
	SDL_Rect windowRect = { 0, 0, BLOCK_WIDTH, BLOCK_HEIGHT };
	SDL_Rect textureRect = { 0, 0, 0, 0 };
	const char* m_sprite = nullptr;
	SDL_Texture* m_texture = nullptr;
	bool powerUpAdded = false;
	sp<Textures> m_textures = nullptr;

	void GetSprite();
};

