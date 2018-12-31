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
	for (int y = 0; y < m_size_Y; y++) {
		for (int x = 0; x < m_size_X; x++) {
			int posX = x * BLOCK_WIDTH;
			int posY = y * BLOCK_HEIGHT;
			const auto block = makesp<Block>(posX, posY, MAP_LAYOUT[y][x]);
			const auto blockIndex = Helpers::getCurrentBlock(posX, posY);
			if (blockIndex.first == 10 && blockIndex.second == 5)
			{
				block->blockHasPowerUp = true;
				block->powerUpType = 0;
			}
			if (blockIndex.first == 4 && blockIndex.second == 3)
			{
				block->blockHasPowerUp = true;
				block->powerUpType = 1;
			}
			if (blockIndex.first == 6 && blockIndex.second == 7)
			{
				block->blockHasPowerUp = true;
				block->powerUpType = 2;
			}
			if (blockIndex.first == 8 && blockIndex.second == 10)
			{
				block->blockHasPowerUp = true;
				block->powerUpType = 3;
			}
			if (blockIndex.first == 2 && blockIndex.second == 9)
			{
				block->blockHasPowerUp = true;
				block->powerUpType = 4;
			}
			tileSet.emplace_back(block);
		}
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
