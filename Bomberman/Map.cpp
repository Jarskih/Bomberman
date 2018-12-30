#include "Map.h"
#include "player.h"
#include "Enemy.h"

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
	if (!mapGenerated)
	{
		for (int y = 0; y < m_size_Y; y++) {
			for (int x = 0; x < m_size_X; x++) {
				int posX = x * BLOCK_WIDTH;
				int posY = y * BLOCK_HEIGHT;
				const auto block = makesp<Block>(posX, posY, MAP_LAYOUT[y][x]);
				const auto blockIndex = Helpers::getCurrentBlock(posX, posY);
				if (blockIndex.first == 10 && blockIndex.second == 2)
				{
					addPowerUp(blockIndex.first, blockIndex.second, 0);
					block->blockHasPowerUp = true;
					block->powerUpType = 0;
				}
				if (blockIndex.first == 5 && blockIndex.second == 4)
				{
					addPowerUp(blockIndex.first, blockIndex.second, 1);
					block->blockHasPowerUp = true;
					block->powerUpType = 1;
				}
				tileSet.emplace_back(block);
			}
		}
		mapGenerated = true;
	}
}
void Map::spawnGameObjects()
{
	const auto player = makesp<Player>(m_renderer);
	m_playerList.push_back(player);

	const auto enemy1 = makesp<Enemy>(EASY, m_renderer, 11, 6);
	const auto enemy2 = makesp<Enemy>(EASY, m_renderer, 9, 8);
	const auto enemy3 = makesp<Enemy>(EASY, m_renderer, 3, 6);
	m_enemyList.push_back(enemy1);
	m_enemyList.push_back(enemy2);
	m_enemyList.push_back(enemy3);
}


void Map::loadTextures()
{
	for (const auto& block : tileSet)
	{
		block->LoadTexture(m_renderer);
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
