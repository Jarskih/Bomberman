#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include <fstream>
#include <iostream>

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
	for (const auto& blocksY : tileSet) {
		for (const auto& blockX : blocksY) {
			blockX->render(m_renderer);
		}
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

void Map::generateMap()
{
	bool levelLoaded = true;

	//Open the map
	std::ifstream map("assets/level1.map");

	//If the map couldn't be loaded
	if (!map.is_open())
	{
		printf("Unable to load map file!\n");
		levelLoaded = false;
	}

	for (int y = 0; y < m_size_y; y++) {
		for (int x = 0; x < m_size_x; x++) {
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
				std::cout << "Error loading map: Unexpected end of file!\n" << std::endl;
				levelLoaded = false;
				break;
			}
			else
			{
				//const auto block = makesp<Block>(posX, posY, MAP_LAYOUT[y][x]);
				sp<Block> block = makesp<Block>(posX, posY, blockType);
				tileSet[x][y] = block;
				//tileSet.emplace_back(block);
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
			x = Helpers::randomNumber(MAX_BLOCKS_X - 1);
			y = Helpers::randomNumber(MAX_BLOCKS_Y - 1);

			// Do not spawn enemies next to player
			if (x < 5 || y < 5)
			{
				continue;
			}

			const auto block = tileSet[x][y];
			if (block->blockType == GRASS)
			{
				const auto enemyObject = makesp<Enemy>(EASY, m_renderer, x, y);
				m_enemyList.push_back(enemyObject);
				allowedBlock = true;
				break;
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
			x = Helpers::randomNumber(MAX_BLOCKS_X - 1);
			y = Helpers::randomNumber(MAX_BLOCKS_Y - 1);

			if (tileSet[x][y]->blockType == BREAKABLE && !tileSet[x][y]->blockHasPowerUp) {
				tileSet[x][y]->blockHasPowerUp = true;
				tileSet[x][y]->powerUpType = powerUpType;
				allowedBlock = true;
				break;
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
	const auto powerUp = makesp<PowerUp>(index_x, index_y, powerUpType, m_renderer);
	powerUps.emplace_back(powerUp);
}

// Get block object from coordinates
sp<Block> Map::findBlockByCoordinates(int x, int y)
{
	auto block = Helpers::getCurrentBlock(x, y);
	return findBlockByIndex(block.first, block.second);
}

sp<Block> Map::findBlockByIndex(int x, int y)
{
	if (x > 0 && y > 0 && x < MAX_BLOCKS_X - 1 && y < MAX_BLOCKS_Y - 1) {
		return tileSet[x][y];
	}
	else
	{
		return nullptr;
	}
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
