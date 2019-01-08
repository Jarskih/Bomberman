#pragma once
#include "Block.h"
#include <vector>
#include "Map.h"
#include <list>

static const int ACTOR_WIDTH = 100;
static const int ACTOR_HEIGHT = 80;
static const int PADDING_X = Config::BLOCK_WIDTH / 10;
static const int PADDING_Y = Config::BLOCK_HEIGHT / 10;

const enum EnemyType
{
	EASY,
	HARD
};

class Map;

class Enemy
{
public:
	Enemy(const EnemyType enemy_type, SDL_Renderer* renderer, const int index_x, const int index_y) :
		m_enemy_type(enemy_type), m_renderer(renderer)
	{
		const auto blockCenter = Helpers::GetBlockCenter(index_x, index_y);
		m_pos_x = blockCenter.first;
		m_pos_y = blockCenter.second;
		if (m_enemy_type == EASY)
		{
			m_speed = 2;
			m_decision_delay = 5000;
		}
		else if (m_enemy_type == HARD)
		{
			m_speed = 3;
			m_decision_delay = 10;
		}
	};
	void update();
	void render();
	void smartMove();

	bool m_is_alive = true;

	enum States { DOWN, UP, LEFT, RIGHT };

	int m_state = DOWN;
	EnemyType m_enemy_type = EASY;
	SDL_Rect m_collider = { 0, 0, Config::BLOCK_WIDTH - PADDING_X, Config::BLOCK_HEIGHT - PADDING_Y };
	void die();
private:
	SDL_Renderer* m_renderer;
	sp<Block> m_next_block{};
	sp<Block> target_block{};
	sp<Block> current_block{};
	int m_pos_x;
	int m_pos_y;
	int m_speed_x = 0;
	int m_speed_y = 0;
	int m_frame = 0;
	int m_score = 100;
	Uint32 m_time_died = 0;
	Uint32 m_death_delay = 1500;
	SDL_Texture* m_texture = nullptr;
	bool m_texture_loaded = false;
	std::string m_sprite = "easyEnemy";
	SDL_Rect m_window_rect = { 0, 0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
	SDL_Rect m_texture_rect = { 0, 0, 0, 0 };
	Uint32 m_decision_time = 0;
	Uint32 m_decision_delay = 0;
	std::list<sp<Block>> m_path{};

	bool m_moving = false;
	int m_speed = 2;

	void loadTexture(std::string sprite);
	void decide();
	void move();
	void randomMove();
};
