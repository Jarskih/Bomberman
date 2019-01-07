#pragma once
#include <vector>
#include <SDL.h>
#include "Helpers.h"
#include "Block.h"
#include "Player.h"
#include "Enemy.h"
#include "Timer.h"
#include "PowerUp.h"
#include "State.h"

class PowerUp;
class Player;
class Enemy;

class Map
{
public:
	Map(SDL_Renderer* renderer) : m_renderer(renderer) {
		generateMap();
		spawnEnemiesAtStart();
		spawnPowerUps();
	};
	~Map() = default;
	void update(sp<Timer> &timer);
	void render(sp<Map> &map) const;
	void handleEvent(SDL_Event& event);
	void addPowerUp(int index_x, int index_y, int powerUpType);
	sp<Block> findBlockByCoordinates(int x, int y);
	sp<Block> findBlockByIndex(int x, int y);
	sp<Block> findRandomGrassBlock();
	static void win();
	void spawnEnemies(int indexX, int indexY, int number, int enemyType);

	//std::vector<sp<Block>> tileSet = {};
	sp<Block> tileSet[Config::MAX_BLOCKS_X][Config::MAX_BLOCKS_Y] = {};
	int m_score = 0;
	int m_players = 1;
	std::vector<sp<Player>> m_playerList = {};
	std::vector<sp<Enemy>> m_enemyList = {};
	std::vector<sp<PowerUp>> m_powerUps = {};
	bool m_level_cleared = false;
private:
	void generateMap();
	void spawnEnemiesAtStart();
	void spawnPowerUps();
	void checkWinCondition();

	int m_size_x = Config::MAX_BLOCKS_X;
	int m_size_y = Config::MAX_BLOCKS_Y;
	SDL_Renderer* m_renderer = nullptr;
	bool m_enemies_dead = false;
	bool m_timeOut = false;
	bool m_spawned_time_out_enemies = false;

};

