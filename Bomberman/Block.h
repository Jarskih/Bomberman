#pragma once
#include <SDL.h>
#include "Config.h"
#include <utility>
#include "Textures.h"
#include "Service.h"

class Block
{
public:
	Block(int x, int y, int blockType) : m_pos_x(x), m_pos_y(y), m_block_type(blockType)
	{
		m_index_x = Helpers::GetCurrentBlock(m_pos_x, m_pos_y).first;
		m_index_y = Helpers::GetCurrentBlock(m_pos_x, m_pos_y).second;
		m_textures = Service<Textures>::Get();
		m_old_block_type = blockType;
		LoadTexture();
	};
	~Block() = default;

	SDL_Rect m_collider = { 0,0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
	void LoadTexture();
	void changeBlockType(int newType);
	std::pair <int, int> getBlockIndex() const;
	void render(SDL_Renderer* renderer);
	int m_index_x;
	int m_index_y;
	int m_pos_x;
	int m_pos_y;
	int m_block_type = -1;
	bool m_block_has_power_up = false;
	int m_power_up_type = 0;

	// A* Pathfinding
	int m_g_cost = 0;
	int m_h_cost = 0;
	int fCost() const { return m_g_cost + m_h_cost; };
	sp<Block> m_parent = nullptr;
private:
	Uint32 timeExploded = 0;
	int m_frame = 0;
	int m_old_block_type;
	bool m_texture_loaded = false;
	bool m_power_up_added = false;
	const char* m_sprite = nullptr;
	SDL_Rect m_window_rect = { 0, 0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
	SDL_Rect m_texture_rect = { 0, 0, 0, 0 };
	SDL_Texture* m_texture = nullptr;
	sp<Textures> m_textures = nullptr;

	void getSprite();
};

