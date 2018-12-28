#pragma once
#include "Block.h"
#include <vector>
#include "Map.h"

static const int ACTOR_WIDTH = 100;
static const int ACTOR_HEIGHT = 80;
static const int PADDING_X = BLOCK_WIDTH / 10;
static const int PADDING_Y = BLOCK_HEIGHT / 10;

const enum EnemyType {
	EASY,
	HARD
};

class Map;

class Enemy {
public:
	Enemy(const EnemyType enemy_type, SDL_Renderer* renderer, const int index_x, const int index_y) :
		m_enemy_type(enemy_type), m_renderer(renderer), m_index_x(index_x), m_index_y(index_y)
	{
		const auto blockCenter = Helpers::getBlockCenter(m_index_x, m_index_y);
		m_pos_x = blockCenter.first;
		m_pos_y = blockCenter.second;
	};
	void update();
	void render();
	void move();

	bool isAlive = true;
	enum states { DOWN, UP, LEFT, RIGHT };
	int state = DOWN;
	EnemyType m_enemy_type = EASY;
	SDL_Rect collider = { 0, 0, BLOCK_WIDTH - PADDING_X, BLOCK_HEIGHT - PADDING_Y };
	void die();
private:
	SDL_Renderer* m_renderer;
	int m_index_x;
	int m_index_y;
	int m_pos_x;
	int m_pos_y;
	int frame = 0;
	int m_score = 100;
	Uint32 timeDied;
	Uint32 deathDelay = 1500;
	SDL_Texture* m_texture = nullptr;
	bool m_texture_loaded = false;
	std::string m_sprite = "easyEnemy";
	SDL_Rect windowRect = { 0, 0, BLOCK_WIDTH, BLOCK_HEIGHT };
	SDL_Rect textureRect = { 0, 0, 0, 0 };
	Uint32 decisionTime = 0;
	const Uint32 decisionDelay = 100000;

	bool moving = false;
	int speed = 1;

	void loadTexture(std::string sprite);
	void decide();
};
