#pragma once
#include "Block.h"
#include <vector>
#include "Map.h"
#include <list>
#include "Entity.h"

static const int ACTOR_WIDTH = 100;
static const int ACTOR_HEIGHT = 80;
static const int PADDING_X = Config::BLOCK_WIDTH / 10;
static const int PADDING_Y = Config::BLOCK_HEIGHT / 10;

class Entity;
class Map;

class Enemy : public Entity
{
public:
	Enemy(const EntityType enemy_type, SDL_Renderer* renderer, const int index_x, const int index_y);;
	void update() override;
	void render() override;
	void smartMove();
	void die();
private:
	SDL_Renderer* m_renderer;
	sp<Block> m_next_block{};
	sp<Block> target_block{};
	sp<Block> current_block{};

	EntityType m_type;
	int m_frame = 0;
	int m_score = 100;
	bool m_texture_loaded = false;
	SDL_Texture* m_texture = nullptr;
	std::string m_sprite;
	Uint32 m_time_died = 0;
	Uint32 m_death_delay = 1500;
	Uint32 m_decision_time = 0;
	Uint32 m_decision_delay = 0;
	std::list<sp<Block>> m_path{};
	int m_old_target_x = 0;
	int m_old_target_y = 0;
	int m_speed = 2;

	void loadTexture(std::string sprite);
	void decide();
	void move();
};
