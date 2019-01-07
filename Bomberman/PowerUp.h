#pragma once
#include <SDL.h>
#include "GameRules.h"
#include "Textures.h"
#include "Service.h"
#include "Map.h"

class Player;

class PowerUp
{
public:
	PowerUp(int index_x, int index_y, int type, SDL_Renderer* renderer) : m_index_x(index_x), m_index_y(index_y), m_type(type), m_renderer(renderer)
	{
		const auto blockCenter = Helpers::GetBlockCenter(m_index_x, m_index_y);
		m_collider.x = blockCenter.first;
		m_collider.y = blockCenter.second;
		m_pos_x = blockCenter.first;
		m_pos_y = blockCenter.second;
		m_window_rect.x = blockCenter.first;
		m_window_rect.y = blockCenter.second;

		m_texture = Service<Textures>::Get()->findTexture("powerUps");

	};
	~PowerUp() = default;
	void render();
	void checkCollision(const std::vector<sp<Player>>& m_playerList);

	enum PowerUpTypes
	{
		FLAME,
		BOMB,
		SPEED,
		LIFE,
		EXIT
	};
private:
	SDL_Rect m_collider = { 0,0,BLOCK_WIDTH, BLOCK_HEIGHT };
	SDL_Texture* m_texture;
	int m_index_x;
	int m_index_y;
	int m_type;
	SDL_Renderer* m_renderer;
	SDL_Rect m_window_rect = { 0, 0, BLOCK_WIDTH, BLOCK_HEIGHT };
	SDL_Rect m_texture_rect = { 0, 0, 0, 0 };
	int m_pos_x;
	int m_pos_y;
	int m_total_frames = 2;
	int m_frame = 0;
	bool m_is_picked_up = false;
	int m_score = 1000;
};

