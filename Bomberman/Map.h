#pragma once
#include <vector>
#include <SDL.h>
#include "Helpers.h"
#include "Block.h"
#include "player.h"
#include "Enemy.h"
#include "Timer.h"
#include "PowerUp.h"

class PowerUp;
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
	void update(sp<Timer> &timer);
	void render(sp<Map> &map) const;
	void handleEvent(SDL_Event& event);
	void addPowerUp(int index_x, int index_y, int powerUpType);
	static void win();

	std::vector<sp<Block>> tileSet = {};
	int m_score = 0;
	int m_players = 1;
	std::vector<sp<Player>> m_playerList = {};
	std::vector<sp<Enemy>> m_enemyList = {};
	bool levelCleared = false;
private:
	void generateMap();
	void spawnGameObjects();
	void checkWinCondition();

	int m_size_Y = 0;
	int m_size_X = 0;
	SDL_Renderer* m_renderer = nullptr;
	bool enemiesDead = false;
	bool m_timeOut = false;
	std::vector<sp<PowerUp>> powerUps = {};
};

