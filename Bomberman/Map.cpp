#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include <fstream>

void Map::update(sp<Timer> &timer)
{
	for (const auto& player : m_playerList)
	{
		player->update();
	}

	for (const auto& enemy : m_enemyList)
	{
		enemy->update();
	}

	if (timer->getTimeLeft() < 0)
	{
		m_timeOut = true;
	}

	for (const auto& powerUp : powerUps)
	{
		powerUp->checkCollision(m_playerList);
	}
	checkWinCondition();
}

void Map::render(sp<Map> &map) const
{
	for (const auto& block : tileSet) {
		block->render(m_renderer);
	}

	for (const auto& powerUp : powerUps)
	{
		powerUp->render();
	}

	for (const auto& player : m_playerList)
	{
		player->render();
	}

	for (const auto& enemy : m_enemyList)
	{
		enemy->render();
	}
}

void Map::generateMap() {

	bool levelLoaded = true;

	//Open the map
	std::ifstream map("assets/level1.map");

	//If the map couldn't be loaded
	if (!map.is_open())
	{
		printf("Unable to load map file!\n");
		levelLoaded = false;
	}

	for (int y = 0; y < m_size_Y; y++) {
		for (int x = 0; x < m_size_X; x++) {
			int posX = x * BLOCK_WIDTH;
			int posY = y * BLOCK_HEIGHT;

			//Determines what kind of block will be made
			int blockType = -1;

			//Read block from map file
			map >> blockType;


			//If the was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				levelLoaded = false;
				break;
			}
			else
			{
				//const auto block = makesp<Block>(posX, posY, MAP_LAYOUT[y][x]);
				const auto block = makesp<Block>(posX, posY, blockType);
				tileSet.emplace_back(block);
			}
		}
	}
}
void Map::spawnGameObjects()
{
	const auto player = makesp<Player>(m_renderer);
	m_playerList.push_back(player);
	;
	int x = 0;
	int y = 0;

	for (int enemy = 0; enemy < NUMBER_OF_ENEMIES; enemy++)
	{
		bool allowedBlock = false;
		while (!allowedBlock)
		{
			x = Helpers::randomNumber(MAX_BLOCKS_X);
			y = Helpers::randomNumber(MAX_BLOCKS_Y);

			// Do not spawn enemies next to player
			if (x < 5 || y < 5)
			{
				continue;
			}

			for (auto & block : tileSet)
			{
				if (block->index_x == x && block->index_y == y && block->blockType == GRASS)
				{
					allowedBlock = true;
					const auto enemyObject = makesp<Enemy>(EASY, m_renderer, x, y);
					m_enemyList.push_back(enemyObject);
					break;
				}
			}
		}
	}
}

void Map::spawnPowerUps()
{
	int x = 0;
	int y = 0;

	for (int powerUpType = 0; powerUpType < 5; powerUpType++)
	{
		bool allowedBlock = false;
		while (!allowedBlock)
		{
			x = Helpers::randomNumber(MAX_BLOCKS_X);
			y = Helpers::randomNumber(MAX_BLOCKS_Y);
			for (auto & block : tileSet)
			{
				if (block->index_x == x && block->index_y == y && block->blockType == BREAKABLE && !block->blockHasPowerUp)
				{
					allowedBlock = true;
					block->blockHasPowerUp = true;
					block->powerUpType = powerUpType;
					break;
				}
			}
		}
	}
}

void Map::handleEvent(SDL_Event& event)
{
	for (const auto& player : m_playerList)
	{
		player->handleEvent(event);
	}
}

void Map::addPowerUp(int index_x, int index_y, int powerUpType)
{
	const auto powerUp = makesp<PowerUp>(index_x - 1, index_y - 1, powerUpType, m_renderer);
	powerUps.emplace_back(powerUp);
}


void Map::checkWinCondition()
{
	int deadEnemies = 0;
	int totalEnemies = 0;
	for (const auto& enemy : m_enemyList)
	{
		totalEnemies++;
		if (!enemy->isAlive)
		{
			deadEnemies++;
		}
	}
	if (deadEnemies >= totalEnemies)
	{
		levelCleared = true;
	}
	else
	{
		levelCleared = false;
	}
}

void Map::win()
{
	Service<State>::Get()->changeScene(State::MENU);
}
