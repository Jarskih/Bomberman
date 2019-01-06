#pragma once
#include <vector>
#include <SDL.h>
#include <array>
#include "Helpers.h"
#include "Block.h"
#include "Player.h"
#include "Enemy.h"
#include "Timer.h"
#include "PowerUp.h"

class PowerUp;
class Player;
class Enemy;

class Map
{
public:
	Map(SDL_Renderer* renderer) : m_renderer(renderer) {
		generateMap();
		spawnGameObjects();
		spawnPowerUps();
	};
	~Map() = default;
	void update(sp<Timer> &timer);
	void render(sp<Map> &map) const;
	void handleEvent(SDL_Event& event);
	void addPowerUp(int index_x, int index_y, int powerUpType);
	sp<Block> findBlockByCoordinates(int x, int y);
	sp<Block> findBlockByIndex(int x, int y);
	static void win();

	//std::vector<sp<Block>> tileSet = {};
	sp<Block> tileSet[MAX_BLOCKS_X][MAX_BLOCKS_Y] = {};
	int m_score = 0;
	int m_players = 1;
	std::vector<sp<Player>> m_playerList = {};
	std::vector<sp<Enemy>> m_enemyList = {};
	bool levelCleared = false;
private:
	void generateMap();
	void spawnGameObjects();
	void spawnPowerUps();
	void checkWinCondition();

	int m_size_x = MAX_BLOCKS_X;
	int m_size_y = MAX_BLOCKS_Y;
	SDL_Renderer* m_renderer = nullptr;
	bool enemiesDead = false;
	bool m_timeOut = false;
	std::vector<sp<PowerUp>> powerUps = {};
};

