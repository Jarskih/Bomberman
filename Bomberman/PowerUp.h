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
		const auto blockCenter = Helpers::getBlockCenter(m_index_x, m_index_y);
		collider.x = blockCenter.first;
		collider.y = blockCenter.second;
		m_pos_x = blockCenter.first;
		m_pos_y = blockCenter.second;
		windowRect.x = blockCenter.first;
		windowRect.y = blockCenter.second;

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
	SDL_Rect collider = { 0,0,BLOCK_WIDTH, BLOCK_HEIGHT };
	SDL_Texture* m_texture;
	int m_index_x;
	int m_index_y;
	int m_type;
	SDL_Renderer* m_renderer;
	SDL_Rect windowRect = { 0, 0, BLOCK_WIDTH, BLOCK_HEIGHT };
	SDL_Rect textureRect = { 0, 0, 0, 0 };
	int m_pos_x;
	int m_pos_y;
	int totalFrames = 2;
	int frame = 0;
	bool isPickedUp = false;
	int m_score = 1000;
};

