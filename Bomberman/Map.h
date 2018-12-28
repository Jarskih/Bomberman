#pragma once
#include <vector>
#include <SDL.h>
#include "Helpers.h"
#include "Block.h"
#include "player.h"
#include "Enemy.h"

class Player;
class Enemy;

class Map
{
public:
	Map(int height, int width, SDL_Renderer* renderer) : m_size_Y(height), m_size_X(width), m_renderer(renderer) {
		generateMap();
		spawnGameObjects();
	};
	~Map() = default;
	void update(sp<Map> &map) const;
	void render(sp<Map> &map) const;
	void loadTextures();
	std::vector<sp<Block>> tileSet = {};
	int m_score = 0;
	int m_players = 1;
	std::vector<sp<Player>> m_playerList = {};
	std::vector<sp<Enemy>> m_enemyList = {};
private:
	int m_size_Y = 0;
	int m_size_X = 0;
	SDL_Renderer* m_renderer = nullptr;
	bool enemiesDead = false;
	void generateMap();
	void spawnGameObjects();
	//std::string blockSprites[9] = { "img/block.png", "img/whiteBlock.png", "img/wallTop.png", "img/wallLeft.png", "img/wallRight.png", "img/wallDown.png", "img/wallTopLeft.png", "img/wallTopRight.png", "img/grass.png" };
};

